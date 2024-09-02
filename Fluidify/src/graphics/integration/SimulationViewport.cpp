#include "SimulationViewport.h"

#include <API/core/RendererCommand.h>
#include <API/core/Renderer.h>

#include <Simulation/Solver.h>

#include <vendor/glm/gtc/matrix_transform.hpp>

#include "Config.h"

#include "Simulation/Solver.h"

FluidGL::SimulationViewport::SimulationViewport(QWidget* parent)
	: OpenGLViewport(parent), orthCamera(0.f, this->size().width(), 0.f, this->size().height()), cellSize({ 0.f, 0.f }), timer(new QTimer(this))
{
	connect(timer, &QTimer::timeout, this, &FluidGL::SimulationViewport::updateViewport);
	timer->start(1);
}

FluidGL::SimulationViewport::~SimulationViewport()
{
	gltDeleteText(textHUD);
	gltTerminate();
}

bool FluidGL::SimulationViewport::init()
{
	updateCellSize();

	float vertices[3 * 4] = {
		0.0f		, 0.0f		, 0.0f,
		cellSize.x	, 0.0f		, 0.0f,
		cellSize.x	, cellSize.y, 0.0f,
		0.0f		, cellSize.y, 0.0f
	};

	// When using instanced rendering only 6 indices are used
	constexpr int faces = 1;
	unsigned int offset = 0;
	unsigned int* indices = new unsigned int[6 * faces];

	for (size_t i = 0; i < faces * 6; i += 6) {
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	ibo.reset(API::Core::IndexBuffer::Create(indices, faces * 6));
	vbo.reset(API::Core::VertexBuffer::Create(4, sizeof(float) * 3));

	vbo->AddVertexData(vertices, sizeof(vertices));

	delete[] indices;

	vbl.reset(API::Core::VertexBufferLayout::Create());
	vbl->Push(API::Core::ShaderDataType::Float3);

	vao.reset(API::Core::VertexArray::Create());
	vao->AddBuffer(*vbo, *vbl);

	tilingShader.reset(API::Core::Shader::Create("assets/shader/tiling_vert.glsl", "assets/shader/tiling_frag.glsl"));
	tilingShader->Bind();

	tilingShader->SetUniformMat4f("u_Transform", glm::mat4(1.f));

	ssbo.reset(API::Core::Buffer::Create(API::Core::Buffer::BufferType::SHADER_STORAGE_BUFFER, NULL, sizeof(float)));
	ssbo->BindBase(1);

	logInit();

	Simulation::Solver::getInstance()->init(128);

	this->setUpdateBehavior(OpenGLViewport::UpdateBehavior::NoPartialUpdate);
	this->updatesEnabled();

	gltextInit();

	return true;
}

bool FluidGL::SimulationViewport::onInit()
{
	return init();
}

void FluidGL::SimulationViewport::onResize()
{
	gltViewport(viewportSize.x, viewportSize.y);

	updateCellSize();
	updateCellVertices();

	orthCamera.UpdateProjectionMat(glm::ortho(0.f, (float)viewportSize.x, 0.f, (float)viewportSize.y, -1.f, 1.f));
}

void FluidGL::SimulationViewport::updateViewport()
{
	onResize();
	static auto lastTime = std::chrono::high_resolution_clock::now();
	simulationStep();
	render();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastTime).count();
	lastTime = currentTime;

	const int fps = (int)(1000.0 / time);
	static int fpsm = 0.f;
	static float timeSinceReset = 0.f;
	timeSinceReset += time;

	if (timeSinceReset > 5000.f) {
		timeSinceReset = 0.f;
		fpsm = 0;
	}

	fpsm = fps > fpsm ? fps : fpsm;

	gltSetText(textHUD, fmt::format("{} fps [max {} fps], {:.2f} ms", fps, fpsm, time).c_str());

	Simulation::Solver::getInstance()->setDt(time * 0.001);
}

void FluidGL::SimulationViewport::onUpdate()
{
	updateViewport();
}

void FluidGL::SimulationViewport::setFramerate(int fps)
{
	const int tpf = 1000 / fps;
	timer->setInterval(tpf);
	OpenGLViewport::setFramerate(fps);

	LOG_CORE_TRACE("Set framerate to {0} fps with a frametime of {1} ms", fps, tpf);
}

void FluidGL::SimulationViewport::render()
{
	makeCurrent();

	API::Core::RenderCommand::SetClearColor({ 0.5, 0.5, 0.2, 1.0 });
	API::Core::RenderCommand::Clear();

	API::Core::DefaultRendererContext::BeginScene();

	tilingShader->Bind();
	tilingShader->SetUniformMat4f("u_ViewProjection", orthCamera.GetViewProjectionMat());
	tilingShader->SetUniform2f("u_TileSize", cellSize.x, cellSize.y);
	tilingShader->SetUniform2i("u_GridDim", cellResolution.x, cellResolution.y);

	API::Core::DefaultRendererContext::SubmitInstancedDraw(vao, ibo, cellResolution.x * cellResolution.y);

	gltBeginDraw();
	gltColor(1.f, 1.f, 1.f, 1.f);
	gltDrawText2D(textHUD, 10, 10, 1);
	gltEndDraw();

	API::Core::DefaultRendererContext::EndScene();
}

void FluidGL::SimulationViewport::simulationStep()
{
	Simulation::Solver::getInstance()->step();

	const Simulation::GridDto gridData = Simulation::Solver::getInstance()->getDensityMatrix(cellResolution.x, cellResolution.y);
	size_t gridSize = gridData.h * gridData.w;

	if (gridData.hasChanged || gridData.hasChangedDim) {
		ssbo->Bind();
		ssbo->SetDataDynamic(gridData.mat, (int)(gridSize * sizeof(float)));
	}
}

void FluidGL::SimulationViewport::setResolution(int x, int y)
{
	cellResolution = { x, y };
	updateCellSize();
	updateCellVertices();
}

void FluidGL::SimulationViewport::addNodeDens(glm::ivec2 node, float dens)
{
	Simulation::Solver::getInstance()->addNodeDens(node.x, node.y, dens);
}

void FluidGL::SimulationViewport::addNodeVel(glm::ivec2 node, glm::vec2 vel)
{
	Simulation::Solver::getInstance()->addNodeVel(node.x, node.y, vel.x, vel.y);
}

void FluidGL::SimulationViewport::onButtonPress(const FLD::ButtonPressEvent& event)
{
	if (prevMousPos.x < 0.f)
		prevMousPos = { event.pos.x, event.pos.y };

	constexpr float velFac = 50.f;

	switch (event.button) {
	case FLD::Button::MOUSE_LEFT:
		Simulation::Solver::getInstance()->addNodeDens(event.pos.x / cellSize.x, event.pos.y / cellSize.y, 15.f);

		glm::vec2 vel = {
			(event.pos.x - prevMousPos.x) / size().width(),
			(event.pos.y - prevMousPos.y) / size().height()
		};

		glm::normalize(vel);

		vel *= velFac;

		Simulation::Solver::getInstance()->addNodeVel(event.pos.x / cellSize.x, event.pos.y / cellSize.y, vel.x, -vel.y);
		break;
	default:
		break;
	}

	prevMousPos = { event.pos.x, event.pos.y };
}

inline void FluidGL::SimulationViewport::updateCellSize()
{
	cellSize = { viewportSize.x / float(cellResolution.x), viewportSize.y / (float)cellResolution.y };
}

void FluidGL::SimulationViewport::updateCellVertices()
{
	float vertices[3 * 4] = {
		0.0f		, 0.0f		, 0.0f,
		cellSize.x	, 0.0f		, 0.0f,
		cellSize.x	, cellSize.y, 0.0f,
		0.0f		, cellSize.y, 0.0f
	};

	vbo->Empty();
	vbo->AddVertexData(vertices, sizeof(vertices));
}

void FluidGL::SimulationViewport::logInit() const
{
	LOG_CORE_TRACE("Detected OpenGL Version: {0}", API::Core::RenderCommand::GetAPIVer());
	LOG_CORE_TRACE("Detected Renderer: {0}", API::Core::RenderCommand::GetGPUID());
	LOG_CORE_TRACE("Detected GPU publisher: {0}", API::Core::RenderCommand::GetPublisher());
	LOG_CORE_TRACE("Detected GLSL Version: {0}", API::Core::RenderCommand::GetShaderLanID());
}

void FluidGL::SimulationViewport::gltextInit()
{
	gltInit();
	textHUD = gltCreateText();
}
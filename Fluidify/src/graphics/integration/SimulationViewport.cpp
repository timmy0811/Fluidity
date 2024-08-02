#include "SimulationViewport.h"

#include <API/core/RendererCommand.h>
#include <API/core/Renderer.h>

#include <Simulation/Sim.h>

#include <vendor/glm/gtc/matrix_transform.hpp>

#include "Config.h"

FluidGL::SimulationViewport::SimulationViewport(QWidget* parent)
	: OpenGLViewport(parent), orthCamera(0.f, FLD::conf.WIN_WIDTH, 0.f, FLD::conf.WIN_HEIGHT), cellSize({ 0.f, 0.f })
{
}

FluidGL::SimulationViewport::~SimulationViewport()
{
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

	ssbo.reset(API::Core::Buffer::Create(API::Core::Buffer::BufferType::SHADER_STORAGE_BUFFER, NULL, sizeof(int)));
	ssbo->BindBase(1);

	logInit();

	return true;
}

bool FluidGL::SimulationViewport::onInit()
{
	return init();
}

void FluidGL::SimulationViewport::onResize()
{
	updateCellSize();
	updateCellVertices();

	orthCamera.UpdateProjectionMat(glm::ortho(0.f, (float)viewportSize.x, 0.f, (float)viewportSize.y, -1.f, 1.f));
}

void FluidGL::SimulationViewport::onUpdate()
{
	// Todo: OnUpdate only executes when viewport changes !!!
	simulationStep();
	render();
}

void FluidGL::SimulationViewport::render()
{
	API::Core::RenderCommand::SetClearColor({ 0.5, 0.5, 0.2, 1.0 });
	API::Core::RenderCommand::Clear();

	API::Core::DefaultRendererContext::BeginScene();

	tilingShader->Bind();
	tilingShader->SetUniformMat4f("u_ViewProjection", orthCamera.GetViewProjectionMat());
	tilingShader->SetUniform2f("u_TileSize", cellSize.x, cellSize.y);
	tilingShader->SetUniform2i("u_GridDim", cellResolution.x, cellResolution.y);

	API::Core::DefaultRendererContext::SubmitInstancedDraw(vao, ibo, cellResolution.x * cellResolution.y);

	API::Core::DefaultRendererContext::EndScene();
}

void FluidGL::SimulationViewport::simulationStep()
{
	const Sim::DensityGrid& gridData = Sim::getDensityMatrix(cellResolution.x, cellResolution.y);
	size_t gridSize = gridData.h * gridData.w;

	if (gridData.hasChanged || gridData.hasChangedDim) {
		ssbo->Bind();
		ssbo->SetDataDynamic(gridData.mat, (int)(gridSize * sizeof(int)));
	}
}

void FluidGL::SimulationViewport::setResolution(int x, int y)
{
	cellResolution = { x, y };
	updateCellSize();
	updateCellVertices();
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
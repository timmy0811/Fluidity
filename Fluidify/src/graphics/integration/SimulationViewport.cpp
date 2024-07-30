#include "SimulationViewport.h"

#include <API/core/RendererCommand.h>
#include <API/core/Renderer.h>

FluidGL::SimulationViewport::SimulationViewport(QWidget* parent)
	: OpenGLViewport(parent), orthCamera(-1.f, 1.f, -1.f, 1.f)
{
}

FluidGL::SimulationViewport::~SimulationViewport()
{
}

bool FluidGL::SimulationViewport::init()
{
	float vertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
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

	tilingShader->SetUniform4f("u_Color", 0.3f, 0.1f, 0.4f, 1.0f);
	tilingShader->SetUniformMat4f("u_Transform", glm::mat4(1.f));

	return true;
}

void FluidGL::SimulationViewport::onResize()
{
}

void FluidGL::SimulationViewport::render()
{
	API::Core::RenderCommand::SetClearColor({ 0.15, 0.1, 0.2, 1.0 });
	API::Core::RenderCommand::Clear();

	API::Core::DefaultRendererContext::BeginScene();

	tilingShader->Bind();
	tilingShader->SetUniformMat4f("u_ViewProjection", orthCamera.GetViewProjectionMat());

	API::Core::DefaultRendererContext::Submit(vao, ibo);

	API::Core::DefaultRendererContext::EndScene();
}
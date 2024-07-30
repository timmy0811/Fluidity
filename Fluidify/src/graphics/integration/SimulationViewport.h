#pragma once

#include <API/core/IndexBuffer.h>
#include <API/core/VertexBuffer.h>
#include <API/core/VertexBufferLayout.h>
#include <API/core/VertexArray.h>

#include <API/core/Shader.h>

#include <vendor/glm/glm.hpp>

#include "Core.h"
#include "graphics/integration/OpenGLViewport.h"
#include "graphics/camera/OrthographicCamera.h"

namespace FluidGL {
	class SimulationViewport : public OpenGLViewport
	{
	public:
		SimulationViewport(QWidget* parent = nullptr);
		~SimulationViewport();

		virtual bool init() override;
		virtual void onResize() override;
		virtual void render() override;

	private:
		FLD::Ref<API::Core::IndexBuffer> ibo;
		FLD::Ref<API::Core::VertexBuffer> vbo;
		FLD::Ref<API::Core::VertexBufferLayout> vbl;
		FLD::Ref<API::Core::VertexArray> vao;

		FLD::Ref<API::Core::Shader> tilingShader;

		FluidGL::OrthographicCamera orthCamera;
		glm::vec3 orthCameraPosition = { 0.f, 0.f, 0.f };
	};
}

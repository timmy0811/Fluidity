#pragma once

#include <API/core/IndexBuffer.h>
#include <API/core/VertexBuffer.h>
#include <API/core/VertexBufferLayout.h>
#include <API/core/VertexArray.h>
#include <API/core/Buffer.h>

#include <API/core/Shader.h>

#include <vendor/glm/glm.hpp>

#include "Core.h"
#include "graphics/integration/OpenGLViewport.h"
#include "graphics/camera/OrthographicCamera.h"
#include "graphics/Input.h"

namespace FluidGL {
	class SimulationViewport : public OpenGLViewport
	{
	public:
		SimulationViewport(QWidget* parent = nullptr);
		~SimulationViewport();

		virtual bool onInit() override;
		virtual void onResize() override;
		virtual void onUpdate() override;

		virtual void setFramerate(int fps) override;

		virtual bool init();
		virtual void render();

		void simulationStep();

		void setResolution(int x, int y);
		inline const glm::ivec2 getResolution() const { return cellResolution; }

		inline void addNodeDens(glm::ivec2 node, float dens);
		inline void addNodeVel(glm::ivec2 node, glm::vec2 vel);

		void onButtonPress(const FLD::ButtonPressEvent& event);

		void updateViewport();

	private:
		inline void updateCellSize();
		void updateCellVertices();

		void logInit() const;
		void gltextInit();

	private:
		FLD::Ref<API::Core::IndexBuffer> ibo;
		FLD::Ref<API::Core::VertexBuffer> vbo;
		FLD::Ref<API::Core::VertexBufferLayout> vbl;
		FLD::Ref<API::Core::VertexArray> vao;

		FLD::Ref<API::Core::Buffer> ssbo;

		FLD::Ref<API::Core::Shader> tilingShader;

		FluidGL::OrthographicCamera orthCamera;
		glm::vec3 orthCameraPosition = { 0.f, 0.f, 0.f };

		glm::vec2 cellSize;
		glm::ivec2 cellResolution = { 64, 64 };

		glm::vec2 prevMousPos = { -1.f, -1.f };

		QTimer* timer;
		GLTtext* textHUD;
	};
}

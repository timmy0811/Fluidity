#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <vendor/glm/glm.hpp>

namespace FluidGL {
	class OpenGLViewport : public QOpenGLWidget, protected QOpenGLFunctions {
		Q_OBJECT

	public:
		OpenGLViewport(QWidget* parent = nullptr);
		~OpenGLViewport();

		virtual bool onInit() = 0;
		virtual void onResize() = 0;
		virtual void onUpdate() = 0;

	protected:
		void initializeGL() override;
		void resizeGL(int w, int h) override;
		void paintGL() override;

	protected:
		QWidget* parent;

		glm::ivec2 viewportSize;
	};
}
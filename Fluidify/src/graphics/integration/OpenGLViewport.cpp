#include <GL/glew.h>

#include "graphics/integration/OpenGLViewport.h"
#include "Log.h"

#include <QDebug>

FluidGL::OpenGLViewport::OpenGLViewport(QWidget* parent)
	: QOpenGLWidget(parent), parent(parent), size({ 0, 0 }) {
}

FluidGL::OpenGLViewport::~OpenGLViewport() {
}

void FluidGL::OpenGLViewport::initializeGL() {
	initializeOpenGLFunctions();

	if (glewInit() != GLEW_OK) {
		LOG_FGL_ERROR("Could not initialize glew");
		return;
	}

	if (!init()) {
		LOG_FGL_ERROR("Could not initialize the simulation viewport");
		return;
	}
}

void FluidGL::OpenGLViewport::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
	size = { w, h };

	onResize();
}

void FluidGL::OpenGLViewport::paintGL() {
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	render();
}
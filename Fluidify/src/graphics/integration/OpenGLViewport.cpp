#include <GL/glew.h>

#include "graphics/integration/OpenGLViewport.h"
#include "Log.h"
#include "Config.h"

#include <QDebug>

FluidGL::OpenGLViewport::OpenGLViewport(QWidget* parent)
	: QOpenGLWidget(parent), parent(parent), viewportSize({ FLD::conf.WIN_WIDTH, FLD::conf.WIN_HEIGHT }) {
}

FluidGL::OpenGLViewport::~OpenGLViewport() {
}

void FluidGL::OpenGLViewport::initializeGL() {
	initializeOpenGLFunctions();

	if (glewInit() != GLEW_OK) {
		LOG_FGL_ERROR("Could not initialize glew");
		return;
	}

	if (!onInit()) {
		LOG_FGL_ERROR("Could not initialize the simulation viewport");
		return;
	}
}

void FluidGL::OpenGLViewport::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
	viewportSize = { w, h };

	onResize();
}

void FluidGL::OpenGLViewport::paintGL() {
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	onUpdate();
}
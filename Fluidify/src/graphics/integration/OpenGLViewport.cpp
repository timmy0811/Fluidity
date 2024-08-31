#include <GL/glew.h>

#include "graphics/integration/OpenGLViewport.h"
#include "Log.h"
#include "Config.h"

#include <QDebug>

FluidGL::OpenGLViewport::OpenGLViewport(QWidget* parent)
	: QOpenGLWidget(parent), parent(parent), viewportSize({ this->size().width(), this->size().height() }) {
}

FluidGL::OpenGLViewport::~OpenGLViewport() {
}

void FluidGL::OpenGLViewport::setFramerate(int fps)
{
	this->fps = fps;
}

const int FluidGL::OpenGLViewport::getFramerate() const
{
	return fps;
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

	// format().setSwapInterval(1);
}

void FluidGL::OpenGLViewport::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
	viewportSize = { w, h };

	onResize();
}

void FluidGL::OpenGLViewport::paintGL() {
	onUpdate();
}
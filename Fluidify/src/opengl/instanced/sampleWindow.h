#pragma once

#include "opengl/openGLWindow.h"

#include <QtOpenGL/qopenglvertexarrayobject.h>
#include <QtOpenGL/qopenglbuffer.h>
#include <QtOpenGL/qopenglshaderprogram.h>

class TriangleWindow : public OpenGLWindow {
public:
	TriangleWindow(QWindow* parent = nullptr) : OpenGLWindow(parent) {};
	~TriangleWindow() override;

	void initialize() override;
	void render() override;

private:
	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vertexBufferObject;
	QOpenGLShaderProgram* m_program;
};
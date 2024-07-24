#include "sampleWindow.h"

TriangleWindow::~TriangleWindow()
{
	m_context->makeCurrent(this);
	m_vao.destroy();
	m_vertexBufferObject.destroy();

	delete m_program;
}

void TriangleWindow::initialize()
{
	m_program = new QOpenGLShaderProgram();

	if (!m_program->addShaderFromSourceFile(
		QOpenGLShader::Vertex, "assets/shader/passthrough_vert.glsl"))
	{
		qDebug() << "Vertex shader errors :\n" << m_program->log();
	}
	if (!m_program->addShaderFromSourceFile(
		QOpenGLShader::Fragment, "assets/shader/uni_color_frag.glsl"))
	{
		qDebug() << "Fragment shader errors :\n" << m_program->log();
	}
	if (!m_program->link())
		qDebug() << "Shader linker errors :\n" << m_program->log();

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	m_vertexBufferObject = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer); // VBO
	m_vertexBufferObject.create();
	m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_vertexBufferObject.bind();
	m_vertexBufferObject.allocate(vertices, sizeof(vertices)); // copy data into buffer

	m_vao.create();
	m_vao.bind();

	m_program->enableAttributeArray(0);
	m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3); // 0: offset of data start; 3: amount of type instances of each vertex

	// unbind all
	m_vertexBufferObject.release();
	m_vao.release();
}

void TriangleWindow::render()
{
	const qreal retinaScale = devicePixelRatio();
	glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_program->bind();
	m_vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);

	m_vao.release();
}
#pragma once

#include <qopenglfunctions.h>
#include <qwindow.h>

class OpenGLWindow : public QWindow, protected QOpenGLFunctions {
	Q_OBJECT

public:
	explicit OpenGLWindow(QWindow* parent = 0);

	virtual void initialize() = 0;
	virtual void render() = 0;

public slots:
	void renderLater();
	void renderNow();

protected:
	bool event(QEvent* event) Q_DECL_OVERRIDE;
	void exposeEvent(QExposeEvent* event) Q_DECL_OVERRIDE;

protected:
	QOpenGLContext* m_context;
};

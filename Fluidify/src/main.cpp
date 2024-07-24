#include "opengl/instanced/sampleWindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	QSurfaceFormat format;

	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(4, 1);
	QSurfaceFormat::setDefaultFormat(format);

	TriangleWindow window;

	window.setFormat(format);
	window.resize(640, 480);
	window.show();

	return a.exec();
}
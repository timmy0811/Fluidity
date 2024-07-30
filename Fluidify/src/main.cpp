#include <QtWidgets/QApplication>
#include <QMainWindow>

#include "Log.h"

#include "graphics/integration/SimulationViewport.h"

#if defined _WIN32 && !defined NDEBUG
#define DEBUG_LOG
#endif

#ifdef DEBUG_LOG
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

int main(int argc, char* argv[])
{
#ifdef DEBUG_LOG
	// Allocates console and show it
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
#endif

	API::LogAPI::Init();
	API::LogAPI::GetCoreLogger()->info("Initialized API-Logging");

	FLD::Log::Init();
	FLD::Log::GetCoreLogger()->info("Initialized FluidifyCore-Logging");
	FLD::Log::GetGLLogger()->info("Initialized FLuidGL-Logging");

	QApplication a(argc, argv);

	QMainWindow mainWindow;
	FluidGL::SimulationViewport* openGLWidget = new FluidGL::SimulationViewport(&mainWindow);
	mainWindow.setCentralWidget(openGLWidget);
	mainWindow.resize(800, 600);
	mainWindow.show();

	return a.exec();
}
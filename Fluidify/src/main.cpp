#include <QtWidgets/QApplication>

#include "Log.h"
#include "Config.h"

#include "qt/FluidMainWindow.h"
#include "graphics/integration/SimulationViewport.h"
#include "Simulation/Log.h"

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
#pragma warning( push )
#pragma warning( disable : 4996 )
	// Allocates console and show it
	AllocConsole();
	std::ignore = freopen("CONOUT$", "w", stdout);
	std::ignore = freopen("CONOUT$", "w", stderr);
	std::ignore = freopen("CONIN$", "r", stdin);
#pragma warning( pop )
#endif

	Simulation::LogSimulation::Init();
	Simulation::LogSimulation::GetCoreLogger()->info("Initialized Simulation-Logging");

	API::LogAPI::Init();
	API::LogAPI::GetCoreLogger()->info("Initialized API-Logging");

	FLD::Log::Init();
	FLD::Log::GetCoreLogger()->info("Initialized FluidifyCore-Logging");
	FLD::Log::GetGLLogger()->info("Initialized FLuidGL-Logging");

	QApplication a(argc, argv);

	FLD::MainWindow mainWindow;
	//mainWindow.resize(FLD::conf.WIN_WIDTH, FLD::conf.WIN_HEIGHT);
	mainWindow.show();

	mainWindow.initViewport();

	return a.exec();
}
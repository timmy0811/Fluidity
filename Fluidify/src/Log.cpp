#include "Log.h"

#include "spdlog/stopwatch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> FLD::Log::s_GLLogger;
std::shared_ptr<spdlog::logger> FLD::Log::s_CoreLogger;

void FLD::Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_CoreLogger = spdlog::stdout_color_mt("Fluidify");
	s_CoreLogger->set_level(spdlog::level::trace);

	s_GLLogger = spdlog::stdout_color_mt("FluidGL");
	s_GLLogger->set_level(spdlog::level::trace);
}
#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Simulation {
	class LogSimulation
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }

		inline static void SetCoreLogLevel(spdlog::level::level_enum level) { s_CoreLogger->set_level(level); }

		inline static void SetCoreLogPattern(const std::string& pattern) { s_CoreLogger->set_pattern(pattern); }

		inline static void FlushLogsPeriodically(unsigned int seconds) { spdlog::flush_every(std::chrono::seconds(seconds)); }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}

#define LOG_SIM_FATAL(...) ::Simulation::LogSimulation::GetCoreLogger()->fatal(__VA_ARGS__)
#define LOG_SIM_ERROR(...) ::Simulation::LogSimulation::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_SIM_WARN(...) ::Simulation::LogSimulation::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_SIM_INFO(...) ::Simulation::LogSimulation::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_SIM_TRACE(...) ::Simulation::LogSimulation::GetCoreLogger()->trace(__VA_ARGS__)

#define LOG_SIM_START_LOCAL_SW(name) spdlog::stopwatch name
#define LOG_SIM_SW_ELAPSED(name) spdlog::debug("Elapsed {0}", name)
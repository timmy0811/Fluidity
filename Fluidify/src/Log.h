#pragma once

#include <spdlog/spdlog.h>

namespace FLD {
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> GetGLLogger() { return s_GLLogger; }

		inline static void SetCoreLogLevel(spdlog::level::level_enum level) { s_CoreLogger->set_level(level); }
		inline static void SetGLLogLevel(spdlog::level::level_enum level) { s_GLLogger->set_level(level); }

		inline static void SetCoreLogPattern(const std::string& pattern) { s_CoreLogger->set_pattern(pattern); }
		inline static void SetGLLogPattern(const std::string& pattern) { s_GLLogger->set_pattern(pattern); }

		inline static void FlushLogsPeriodically(unsigned int seconds) { spdlog::flush_every(std::chrono::seconds(seconds)); }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_GLLogger;
	};
}

#define LOG_CORE_FATAL(...) ::FLD::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define LOG_CORE_ERROR(...) ::FLD::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_WARN(...) ::FLD::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_INFO(...) ::FLD::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_TRACE(...) ::FLD::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define LOG_FGL_FATAL(...) ::FLD::Log::GetGLLogger()->fatal(__VA_ARGS__)
#define LOG_FGL_ERROR(...) ::FLD::Log::GetGLLogger()->error(__VA_ARGS__)
#define LOG_FGL_WARN(...) ::FLD::Log::GetGLLogger()->warn(__VA_ARGS__)
#define LOG_FGL_INFO(...) ::FLD::Log::GetGLLogger()->info(__VA_ARGS__)
#define LOG_FGL_TRACE(...) ::FLD::Log::GetGLLogger()->trace(__VA_ARGS__)

#define LOG_START_LOCAL_SW(name) spdlog::stopwatch name
#define LOG_SW_ELAPSED(name) spdlog::debug("Elapsed {0}", name)
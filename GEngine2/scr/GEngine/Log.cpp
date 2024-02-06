#include "gepch.h"
#include "Log.h"
#include"spdlog/sinks/stdout_color_sinks.h"

namespace GEngine {
	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stderr_color_mt("GEngine");
		coreLogger->set_level(spdlog::level::trace);

		clientLogger = spdlog::stderr_color_mt("APP");
		clientLogger->set_level(spdlog::level::trace);
	}
}
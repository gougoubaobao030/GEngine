#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Core.h"


namespace GEngine{
	class WIN_API Log
	{
	public:
		static void Init();

		//just get set useline
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }
		
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;


	};
}
 //Core log macros
#define GE_CORE_TRACE(...)    ::GEngine::Log::getCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...)     ::GEngine::Log::getCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...)     ::GEngine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROR(...)    ::GEngine::Log::getCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_CRITICAL(...) ::GEngine::Log::getCoreLogger()->critical(__VA_ARGS__)
								
// Clignt log macros			
#define GE_TRACE(...)         ::GEngine::Log::getClientLogger()->trace(__VA_ARGS__)
#define GE_INFO(...)          ::GEngine::Log::getClientLogger()->info(__VA_ARGS__)
#define GE_WARN(...)          ::GEngine::Log::getClientLogger()->warn(__VA_ARGS__)
#define GE_ERROR(...)         ::GEngine::Log::getClientLogger()->error(__VA_ARGS__)
#define GE_CRITICAL(...)      ::GEngine::Log::getClientLogger()->critical(__VA_ARGS__)

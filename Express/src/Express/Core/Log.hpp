#pragma once

#include "Express/Core/Core.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> //for custom formats

namespace Express
{

	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger> GetClientLogger() { return s_ClientLogger; }
		inline static Ref<spdlog::logger> GetCoreLogger()	{ return s_CoreLogger; }
	private:
		Log() = default; //Makes sure that there can be no instance created of this class
		~Log() = default;

		static Ref<spdlog::logger> s_ClientLogger;
		static Ref<spdlog::logger> s_CoreLogger;
	};

}

//Core logging macros
#ifndef EX_DIST //Distribution version
#define EX_CORE_TRACE(...)			Express::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EX_CORE_INFO(...)			Express::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EX_CORE_WARN(...)			Express::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EX_CORE_ERROR(...)			Express::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EX_CORE_CRITICAL(...)		Express::Log::GetCoreLogger()->critical(__VA_ARGS__)

#else
#define EX_CORE_TRACE(...)			
#define EX_CORE_INFO(...)			
#define EX_CORE_WARN(...)			
#define EX_CORE_ERROR(...)			
#define EX_CORE_CRITICAL(...)		

#endif

//Client loggging macros
#define EX_TRACE(...)			Express::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EX_INFO(...)			Express::Log::GetClientLogger()->info(__VA_ARGS__)
#define EX_WARN(...)			Express::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EX_ERROR(...)			Express::Log::GetClientLogger()->error(__VA_ARGS__)
#define EX_CRITICAL(...)		Express::Log::GetClientLogger()->critical(__VA_ARGS__)

//Assert
#define EX_CORE_ASSERT(x, ...) { if(!(x)) { EX_CORE_CRITICAL("Assertion failed: {0} ", __VA_ARGS__); __debugbreak; } }
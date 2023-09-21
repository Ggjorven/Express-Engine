#include "expch.h"
#include "Log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Express
{

	Ref<spdlog::logger>		Log::s_ClientLogger;
	Ref<spdlog::logger>		Log::s_CoreLogger;


	void Log::Init()
	{

		spdlog::set_pattern("%^[%T] [%L] [%n]: %v%$"); //Time - Level - Name: Message

		s_CoreLogger = spdlog::stdout_color_mt("EXPRESS");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

		//EX_CORE_INFO("Initialized logging system...");
	}

}
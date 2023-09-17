#include "expch.h"
#include "Application.hpp"

#include "Express/Core/Log.hpp"

namespace Express
{
	Application::Application()
		: m_Running(true)
	{
		Init();
	}

	Application::~Application()
	{
		EX_TRACE("Application finished, waiting for user input...");
		std::cin.get(); //So the exe doesn't immediately close
	}

	void Application::Run()
	{
		while (m_Running)
		{

		}
	}

	void Application::Init()
	{
		Log::Init();
	}
}
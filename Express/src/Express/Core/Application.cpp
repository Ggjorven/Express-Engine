#include "expch.h"
#include "Application.hpp"

#include "Express/Core/Log.hpp"

#include "Platforms/Windows/WindowsWindow.hpp"

namespace Express
{
	Application::Application()
		: m_Running(true)
	{
		Init();
	}

	Application::~Application()
	{
		//EX_TRACE("Application finished, waiting for user input...");
		//std::cin.get(); //So the exe doesn't immediately close
	}

	void Application::OnEvent(Event& e)
	{
		EventHandler handler(e);
		handler.Handle<WindowCloseEvent>(EX_BIND_EVENT_FN(Application::OnWindowClose));
		handler.Handle<WindowResizeEvent>(EX_BIND_EVENT_FN(Application::OnWindowResize));

		//EX_WARN("[Event]: {0}", e.ToString());
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_window->OnUpdate();
		}
	}

	void Application::Init()
	{
		Log::Init();
		m_window = Window::Create();

		m_window->SetEventCallBack(EX_BIND_EVENT_FN(Application::OnEvent));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return true;
	}
}
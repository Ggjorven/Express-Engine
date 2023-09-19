#include "expch.h"
#include "Application.hpp"

#include "Express/Core/Log.hpp"

#include "Platforms/Windows/WindowsWindow.hpp"

#include "Express/Renderer/Renderer.hpp"
#include "Express/Renderer/RendererCommand.hpp"

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
		Renderer::Shutdown();
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
			RendererCommand::Clear(); //Not in thecherno's version, but we need to clear the buffers somehow?

			m_window->OnUpdate();

			//Draw
		}
	}

	void Application::Init()
	{
		Log::Init();
		m_window = Window::Create();

		Renderer::Init();

		m_window->SetEventCallBack(EX_BIND_EVENT_FN(Application::OnEvent));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_minimized = true;
			return true;
		}

		m_minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return true;
	}
}
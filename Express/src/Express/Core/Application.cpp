#include "expch.h"
#include "Application.hpp"

#include "Express/Core/Log.hpp"

#include "Platforms/Windows/WindowsWindow.hpp"

#include "Express/Renderer/Renderer.hpp"
#include "Express/Renderer/RendererCommand.hpp"

namespace Express
{
	Application* Application::s_Instance = nullptr;


	Application::Application()
		: m_Running(true), m_LastTime(0.0f)
	{
		Init();
	}

	Application::~Application()
	{
		//EX_TRACE("Application finished, waiting for user input...");
		//std::cin.get(); //So the exe doesn't immediately close
		Renderer::Shutdown();

		for (Layer* layer : m_LayerStack)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventHandler handler(e);

		handler.Handle<WindowCloseEvent>(EX_BIND_EVENT_FN(Application::OnWindowClose));
		handler.Handle<WindowResizeEvent>(EX_BIND_EVENT_FN(Application::OnWindowResize));

		for (Layer* layer : m_LayerStack)
			layer->OnEvent(e);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			//Update deltaTime
			float currentTime = (float)glfwGetTime();
			TimeStep deltaTime(currentTime - m_LastTime);
			//EX_CORE_WARN("DeltaTime: {0}", deltaTime);

			RendererCommand::Clear(); //Not in thecherno's version, but we need to clear the buffers somehow?

			m_Window->OnUpdate();

			//Update & Render layers
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(deltaTime);
				layer->OnRender();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			
			m_Window->OnRender();

			//Update deltaTime
			m_LastTime = currentTime;
		}
	}

	void Application::AddLayer(Layer* layer)
	{
		m_LayerStack.AddLayer(layer);
	}

	void Application::AddOverlay(Layer* layer)
	{
		m_LayerStack.AddOverlay(layer);
	}

	void Application::Init()
	{
		Log::Init();

		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallBack(EX_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new BaseImGuiLayer();
		AddOverlay(m_ImGuiLayer);
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
			m_Minimized = true;
			return true;
		}

		m_Minimized = false;

		//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight()); //So the vertices say the same
		return true;
	}
}
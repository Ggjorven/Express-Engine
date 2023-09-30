#pragma once
#include "expch.h"

#include "Express/Core/Window.hpp"

#include "Express/Events/Event.hpp"
#include "Express/Events/ApplicationEvent.hpp"

#include "Express/Core/LayerStack.hpp"

namespace Express
{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

		void AddLayer(Layer* layer);
		void AddOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		void Init();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e); 
	private:
		Scope<Window> m_Window;
		bool m_Running;
		bool m_Minimized;

		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;

		//For timestep
		float m_LastTime;
	};

	Application* CreateApplication();

}
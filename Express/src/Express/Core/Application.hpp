#pragma once
#include "expch.h"

#include "Express/Core/Window.hpp"

//#include "Express/Events/Event.hpp"
//#include "Express/Events/ApplicationEvent.hpp"

namespace Express
{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		//void OnEvent(Event& e);

		void Run();
	private:
		void Init();

		//void OnWindowClose(WindowClosedEvent& e); //TODO events
	private:
		Scope<Window> m_window;
		bool m_Running;
	};

	Application* CreateApplication();

}
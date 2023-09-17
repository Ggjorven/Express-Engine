#pragma once
#include "expch.h"

//#include "Express/Events/Event.hpp"
//#include "Express/Events/ApplicationEvent.hpp"

namespace Express
{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		void Init();

		//void OnWindowClose(WindowClosedEvent& e); //TODO events
	private:
		bool m_Running;
	};

	Application* CreateApplication();

}
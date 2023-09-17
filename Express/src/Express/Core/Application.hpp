#pragma once
#include "expch.h"

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
	};

	Application* CreateApplication();

}
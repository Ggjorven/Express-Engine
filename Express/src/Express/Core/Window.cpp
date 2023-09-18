#include "expch.h"
#include "Window.hpp"

#include "Platforms/Windows/WindowsWindow.hpp"

namespace Express
{
	Scope<Window> Window::Create(const WindowProperties properties)
	{
		#ifdef EX_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(properties);
		#endif
	}
}
#include "expch.h"
#include "WindowsWindow.hpp"

#include "Express/Core/Log.hpp"

namespace Express
{
	bool WindowsWindow::s_GLFWinitialized = false;


	WindowsWindow::WindowsWindow(const WindowProperties properties)
	{
		if (Init(properties))
			EX_CORE_INFO("WindowsWindow created!");
	}

	WindowsWindow::~WindowsWindow()
	{
		EX_CORE_INFO("WindowsWindow destroyed...");
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		//TODO remove this, temporary, needs to be in a OpenGLContext : GraphicsContext class
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_data.Vsync = enabled;
	}


	bool WindowsWindow::Init(WindowProperties properties)
	{
		//Setup
		int succes = glfwInit();
		if (!succes)
		{
			EX_CRITICAL("Failed to initialize GLFW.");
			return 0;
		}
		glfwSetErrorCallback(ErrorCallBack);

		//Window creation
		m_window = glfwCreateWindow((int)properties.Width, (int)properties.Height, properties.Name.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);

		glfwSetWindowUserPointer(m_window, &m_data); //So we can access the data

		//Graphics context init //TODO

		//Event system //TODO
		

		return 1;
	}

	void WindowsWindow::ErrorCallBack(int errorCode, const char* description)
	{
		EX_ERROR("GLFW error ({0}) ... {1}", errorCode, description);
	}

}
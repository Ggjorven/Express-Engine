#include "expch.h"
#include "OpenGLContext.hpp"

#include "Express/Core/Log.hpp"

#include <GL/glew.h>
#include <GL/GL.h>

namespace Express
{

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_windowHandle(window)
	{
		//EX_WARN("OpenGL Constructor.");
		if (window == nullptr) EX_CRITICAL("Window handle passed in is a nullptr! {0} {1}", __FILE__, __LINE__);
	}

	void OpenGLContext::Init()
	{
		//EX_WARN("OpenGL Init.");
		glfwMakeContextCurrent(m_windowHandle);
		int status = glewInit();
		if (status != GLEW_OK) EX_CORE_CRITICAL("Failed to initialize Glad!");

		EX_CORE_INFO("OpenGL Info:");
		EX_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		EX_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		EX_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		//EX_WARN("OpenGL SwapBuffers.");
		glfwSwapBuffers(m_windowHandle);
	}

}
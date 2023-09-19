#include "expch.h"
#include "OpenGLContext.hpp"

#include "Express/Core/Log.hpp"

#include <glad/glad.h>
#include <GL/GL.h>

namespace Express
{

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_windowHandle(window)
	{
		if (window == nullptr) EX_CRITICAL("Window handle passed in is a nullptr! {0} {1}", __FILE__, __LINE__);
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 0) EX_CORE_CRITICAL("Failed to initialize Glad!");

		EX_CORE_INFO("OpenGL Info:");
		EX_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		EX_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		EX_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}
#pragma once

#include "Express/Core/Core.hpp"

#include <GLFW/glfw3.h>

#include "Express/Renderer/GraphicsContext.hpp"

namespace Express
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_windowHandle;
	};
}
#include "expch.h"
#include "GraphicsContext.hpp"

#include <GLFW/glfw3.h>

#include "Express/Renderer/Renderer.hpp"
#include "Express/Core/Log.hpp"

#include "RenderingAPIs/OpenGL/OpenGLContext.hpp"

namespace Express
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EX_CORE_CRITICAL("Rendering API: None is not allowed {0} {1}", __FILE__, __LINE__);
		case RendererAPI::API::OpenGL: return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		return nullptr;
	}
}
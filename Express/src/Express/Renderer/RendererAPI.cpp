#include "expch.h"
#include "RendererAPI.hpp"

#include "Express/Core/Log.hpp"

//#include "RenderingAPIs/OpenGL/OpenGLRendererAPI.hpp"

namespace Express
{
																	//
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::None; //Select RendererAPI here
																	//
	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None: EX_CORE_CRITICAL("No RendererAPI selected... {0} : {1}", __FILE__, __LINE__);
		//case RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
		}

		return nullptr;
	}
}
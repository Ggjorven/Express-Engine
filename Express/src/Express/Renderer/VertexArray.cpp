#include "expch.h"
#include "VertexArray.hpp"

#include "Express/Core/Log.hpp"

#include "Renderer.hpp"
//#include "RenderingAPIs/OpenGL/OpenGLVertexArray.hpp"

namespace Express
{

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EX_CORE_ASSERT(false, "RendereringAPI none not supported."); break;
		//case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		EX_CORE_ASSERT(false, "No proper RenderingAPI selected.");
		return nullptr;
	}

}
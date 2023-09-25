#include "expch.h"
#include "Texture.hpp"

#include "Express/Renderer/Renderer.hpp"

#include "RenderingAPIs/OpenGL/OpenGLTexture.hpp"

namespace Express
{

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EX_CORE_ASSERT(false, "RendererAPI::API::None not supported.");
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}

		EX_CORE_ASSERT(false, "No valid API selected.");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EX_CORE_ASSERT(false, "RendererAPI::API::None not supported.");
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}

		EX_CORE_ASSERT(false, "No valid API selected.");
		return nullptr;
	}
}
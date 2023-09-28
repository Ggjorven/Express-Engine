#include "expch.h"
#include "Renderer.hpp"

#include "Express/Renderer/RendererCommand.hpp"
#include "Express/Renderer/Renderer2D.hpp"

namespace Express
{

	void Renderer::Init()
	{
		RendererCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RendererCommand::SetViewPort(0, 0, width, height);
	}

}
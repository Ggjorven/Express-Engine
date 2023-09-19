#include "expch.h"
#include "Renderer.hpp"

#include "Express/Renderer/RendererCommand.hpp"

namespace Express
{

	void Renderer::Init()
	{
		RendererCommand::Init();
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RendererCommand::SetViewPort(0, 0, width, height);
	}

}
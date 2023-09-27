#include "expch.h"
#include "RendererCommand.hpp"

namespace Express
{

	Scope<RendererAPI> RendererCommand::s_RendererAPI = RendererAPI::Create(); //Creates an instance of the proper rendererAPI


	void RendererCommand::Init()
	{
		s_RendererAPI->Init();
	}

	void RendererCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RendererCommand::SetClearColour(const glm::vec4& colour)
	{
		s_RendererAPI->SetClearColour(colour);
	}

	void RendererCommand::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewPort(x, y, width, height);
	}

	void RendererCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		s_RendererAPI->DrawIndexed(vertexArray);
	}

	void RendererCommand::DrawIndexed(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader) 
	{
		s_RendererAPI->DrawIndexed(vertexArray, shader);
	}

}
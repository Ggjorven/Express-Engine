#pragma once

#include "Express/Core/Core.hpp"

#include <glm/glm.hpp>

#include "Express/Renderer/RendererAPI.hpp"
#include "Express/Renderer/VertexArray.hpp"

namespace Express
{

	//A class used to send the proper rendering commands to the proper renderering API
	class RendererCommand
	{
	public:
		static void Init();
		static void Clear();
		static void SetClearColour(const glm::vec4& colour);
		static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		static void DrawIndexed(const Ref<VertexArray>& vertexArray);

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};

}
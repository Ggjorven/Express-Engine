#pragma once

#include "Express/Core/Core.hpp"

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Express/Renderer/RendererAPI.hpp"

namespace Express
{

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		void Clear() override;
		void SetClearColour(const glm::vec4& colour) override;
		void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		void DrawIndexed(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader) override;
	private:
		GLuint m_UnusedIds = 0;
	};
}
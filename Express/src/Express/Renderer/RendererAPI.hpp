#pragma once

#include "Express/Core/Core.hpp"

#include <glm/glm.hpp>

namespace Express
{

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL
		};

	public:
		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void SetClearColour(const glm::vec4& colour) = 0;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		inline static API GetAPI() { return s_API; }

		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};
}
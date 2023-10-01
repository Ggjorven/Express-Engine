#pragma once

#include "Express/Core/Core.hpp"

#include <glm/glm.hpp>

#include "Express/Renderer/Texture.hpp"

#include "Express/Renderer/OrthoGraphicCamera.hpp"

namespace Express
{

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		//static void BeginScene(const OrthographicCamera& camera); //TODO
		static void EndScene();

		// Drawing functions
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera = nullptr);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera = nullptr, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

	private:
	};

}
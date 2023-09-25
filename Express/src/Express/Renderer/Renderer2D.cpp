#include "expch.h"
#include "Renderer2D.hpp"

#include "Express/Renderer/VertexArray.hpp"
#include "Express/Renderer/Shader.hpp"
#include "Express/Renderer/RendererCommand.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Express
{
	struct Renderer2DStorage
	{
	public:
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_QuadData;


	void Renderer2D::Init()
	{
		s_QuadData = new Renderer2DStorage();
		s_QuadData->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_QuadData->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_QuadData->QuadVertexArray->AddIndexBuffer(squareIB);

		s_QuadData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_QuadData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		ShaderSource shaderSource = Shader::Read("assets/shaders/Texture.glsl");
		s_QuadData->TextureShader = Shader::Create("TextureShader", shaderSource.VertexSource, shaderSource.FragmentSource);
		s_QuadData->TextureShader->Bind();
		s_QuadData->TextureShader->SetUniformInt1("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_QuadData;
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_QuadData->TextureShader->Bind();
		s_QuadData->TextureShader->SetUniformFloat4("u_Color", color);

		s_QuadData->WhiteTexture->Bind();
		
		s_QuadData->TextureShader->Bind();
		//s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);

		s_QuadData->QuadVertexArray->Bind();
		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
	}

}
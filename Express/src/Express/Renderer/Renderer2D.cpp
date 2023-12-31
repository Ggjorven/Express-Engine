#include "expch.h"
#include "Renderer2D.hpp"

#include "Express/Renderer/VertexArray.hpp"
#include "Express/Renderer/Shader.hpp"
#include "Express/Renderer/RendererCommand.hpp"

#include "Express/Core/Application.hpp"

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

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		// Create Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
		s_QuadData->QuadVertexArray = Express::VertexArray::Create();

		Express::Ref<Express::VertexBuffer> VertexBuffer = Express::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		VertexBuffer->SetLayout({ 
			Express::BufferElement(Express::ShaderDataType::Float3, "a_Position", false), 
			Express::BufferElement(Express::ShaderDataType::Float2, "a_TexCoord", false) 
			});

		Express::Ref<Express::IndexBuffer> IndexBuffer = Express::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		// Bind the VAO first, then bind and set VBO and IBO data
		s_QuadData->QuadVertexArray->Bind();

		s_QuadData->QuadVertexArray->AddVertexBuffer(VertexBuffer);
		s_QuadData->QuadVertexArray->AddIndexBuffer(IndexBuffer);


		//Texture & Shader
		s_QuadData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;

		s_QuadData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));


		ShaderSource shaderSource = ShaderLib::GetShaderSource(ShaderLib::Type::Textured_Coloured_Transform_ViewProj);
		s_QuadData->TextureShader = Shader::Create("TexturedShader", shaderSource.VertexSource, shaderSource.FragmentSource);

		s_QuadData->TextureShader->SetUniformInt1("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_QuadData;
	}

	void Renderer2D::EndScene()
	{
	}

	//================
	//Coloured Quads
	//================
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, camera, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		//TODO make it proper pixel space
		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x / aspectRatio / 400.0f, position.y / aspectRatio / 400.0f, position.z  })
			* glm::scale(glm::mat4(1.0f), { size.x / aspectRatio / 400.0f, size.y / aspectRatio / 400.0f, 1.0f });

		s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);

		if (camera != nullptr) s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));

		s_QuadData->TextureShader->SetUniformFloat4("u_Colour", color);


		s_QuadData->WhiteTexture->Bind();
		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray, s_QuadData->TextureShader);
	}

	//+ rotation
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, camera, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		//TODO make it proper pixel space
		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x / aspectRatio / 400.0f, position.y / aspectRatio / 400.0f, position.z })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x / aspectRatio / 400.0f, size.y / aspectRatio / 400.0f, 1.0f });

		s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);

		if (camera != nullptr) s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));

		s_QuadData->TextureShader->SetUniformFloat4("u_Colour", color);

		s_QuadData->WhiteTexture->Bind();

		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray, s_QuadData->TextureShader);
	}

	//================
	//Textured quads
	//================
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, camera);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera)
	{
		//TODO make it proper pixel space
		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x / aspectRatio / 400.0f, position.y / aspectRatio / 400.0f, position.z })
			* glm::scale(glm::mat4(1.0f), { size.x / aspectRatio / 400.0f, size.y / aspectRatio / 400.0f, 1.0f });

		s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);

		if (camera != nullptr) s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));

		s_QuadData->TextureShader->SetUniformFloat4("u_Colour", glm::vec4(1.0f));

		texture->Bind();

		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray, s_QuadData->TextureShader);
	}

	//+ rotation
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, camera, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const Ref<OrthoGraphicCamera>& camera, const glm::vec4& color)
	{
		//TODO make it proper pixel space
		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x / aspectRatio / 400.0f, position.y / aspectRatio / 400.0f, position.z})
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x / aspectRatio / 400.0f, size.y / aspectRatio / 400.0f, 1.0f}); //Size into pixel space TODO

		s_QuadData->TextureShader->SetUniformMat4("u_Transform", transform);

		if (camera != nullptr) s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", camera->GetViewProjectionMatrix());
		else s_QuadData->TextureShader->SetUniformMat4("u_ViewProj", glm::mat4(1.0f));

		s_QuadData->TextureShader->SetUniformFloat4("u_Colour", glm::vec4(1.0f));

		texture->Bind();

		RendererCommand::DrawIndexed(s_QuadData->QuadVertexArray, s_QuadData->TextureShader);
	}

}
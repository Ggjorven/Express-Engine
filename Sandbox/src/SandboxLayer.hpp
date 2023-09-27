#pragma once

#include <Express/Express.hpp>

class SandboxLayer : public Express::Layer
{
public:
	SandboxLayer() { m_DebugName = "SandboxLayer"; }
	virtual ~SandboxLayer() {}

	void OnAttach() override
	{
		Express::RendererCommand::SetClearColour(glm::vec4(0.2f, 0.3f, 0.2f, 1.0f));

		float vertices[] =
		{
			 0.0f,  0.5f,
			-0.5f, -0.5f,
			 0.5f, -0.5f
		};

		unsigned int indices[] =
		{
			0, 1, 2
		};

		m_VertexArray = Express::VertexArray::Create();

		Express::Ref<Express::VertexBuffer> VBO;
		VBO = Express::VertexBuffer::Create(vertices, sizeof(vertices));
		VBO->SetLayout(Express::BufferLayout({ Express::BufferElement(Express::ShaderDataType::Float2, "a_Position", false) }));

		Express::Ref<Express::IndexBuffer> IBO;
		IBO = Express::IndexBuffer::Create(indices, 6);

		m_VertexArray->AddVertexBuffer(VBO);
		m_VertexArray->AddIndexBuffer(IBO);

		m_Shader = Express::Shader::Create("BasicShader", Express::Shader::Read("assets/shaders/basic.glsl").VertexSource, Express::Shader::Read("assets/shaders/basic.glsl").FragmentSource);

		m_Shader->SetUniformFloat4("u_Colour", glm::vec4(0.9f, 0.5f, 0.5f, 1.0f));
	}


	void OnUpdate() override
	{
		Express::RendererCommand::DrawIndexed(m_VertexArray, m_Shader);
	}



	void OnImGuiRender() override {}
	void OnEvent(Express::Event& e) override {}
	void OnDetach() override {}

private:
	Express::Ref<Express::VertexArray> m_VertexArray;

	Express::Ref<Express::Shader> m_Shader;
};
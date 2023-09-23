#include "SandboxLayer.hpp"



SandboxLayer::SandboxLayer()
{
	m_DebugName = "SandboxLayer";
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnAttach()
{
	float vertices[] = 
	{
		 0.0f, 0.5f,
		-0.5f, -0.5f,
		 0.5f, 0.5f
	};

	unsigned int indices[] =
	{
		0, 1, 2
	};

	m_VertexBuffer = Express::VertexBuffer::Create(vertices, sizeof(vertices));
	m_IndexBuffer = Express::IndexBuffer::Create(indices, sizeof(indices));
	m_Shader = Express::Shader::Create("name", Express::Shader::Read("assets/shaders/basic.glsl").VertexSource, Express::Shader::Read("assets/shaders/basic.glsl").FragmentSource);
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate()
{
	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();
	m_Shader->Bind();

	//Express::RendererCommand::Submit;
}

void SandboxLayer::OnImGuiRender()
{
}

void SandboxLayer::OnEvent(Express::Event& e)
{
}

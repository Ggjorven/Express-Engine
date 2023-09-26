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

	m_VertexBuffer = Express::VertexBuffer::Create(vertices, sizeof(vertices));
	m_VertexBuffer->SetLayout(Express::BufferLayout({ Express::BufferElement(Express::ShaderDataType::Float2, "a_Position", false) }));

	m_IndexBuffer = Express::IndexBuffer::Create(indices, 6);

	m_VertexArray = Express::VertexArray::Create();
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	m_VertexArray->AddIndexBuffer(m_IndexBuffer);

	m_Shader = Express::Shader::Create("name", Express::Shader::Read("assets/shaders/basic.glsl").VertexSource, Express::Shader::Read("assets/shaders/basic.glsl").FragmentSource);
	
	m_Shader->Bind();
	m_Shader->SetUniformFloat4("u_Colour", glm::vec4(0.9f, 0.5f, 0.5f, 1.0f));
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate()
{
	m_Shader->Bind();
	//m_IndexBuffer->Bind();
	m_VertexArray->Bind();

	//Express::RendererCommand::DrawIndexed(m_VertexArray);

	Express::Renderer2D::DrawQuad(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//Express::Renderer2D::DrawQuad(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void SandboxLayer::OnImGuiRender()
{
}

void SandboxLayer::OnEvent(Express::Event& e)
{
	Express::EventHandler handler(e);

	handler.Handle<Express::WindowResizeEvent>(EX_BIND_EVENT_FN(SandboxLayer::ResizeEvent));
}

bool SandboxLayer::ResizeEvent(Express::WindowResizeEvent& e)
{
	//EX_WARN("Resize event");
	Express::RendererCommand::SetViewPort(0, 0, 1280, 720);
	return true;
}
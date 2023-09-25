#pragma once

#include <Express/Express.hpp>

class SandboxLayer : public Express::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate() override;
	void OnImGuiRender() override;
	void OnEvent(Express::Event& e) override;

private:
	bool ResizeEvent(Express::WindowResizeEvent& e);

private:
	Express::Ref<Express::VertexBuffer> m_VertexBuffer;
	Express::Ref<Express::IndexBuffer> m_IndexBuffer;
	Express::Ref<Express::VertexArray> m_VertexArray;

	Express::Ref<Express::Shader> m_Shader;
};
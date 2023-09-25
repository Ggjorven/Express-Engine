#pragma once

#include "Express/Core/Core.hpp"

#include "Express/Renderer/VertexArray.hpp"

namespace Express
{

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		void Bind() const override;
		void UnBind() const override;

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

	private:

	private:
		uint32_t m_RendererID;
		
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		uint32_t m_VertexBufferIndex;

		Ref<IndexBuffer> m_IndexBuffer;
	};

}
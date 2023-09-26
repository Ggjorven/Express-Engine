#include "expch.h"
#include "OpenGLRendererAPI.hpp"

#include "Express/Core/Log.hpp"

namespace Express
{

	static void APIENTRY ErrorCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		EX_CORE_ERROR("[OpenGL]: type: {0}, id: {1}, severity: {2}, message: {3}", type, id, severity, message); //TODO, might need to change this up a bit, but works for now
		EX_CORE_ASSERT(false, "^OPENGL ERROR^");
	}

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ErrorCallBack, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &m_UnusedIds, true);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColour(const glm::vec4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void OpenGLRendererAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		//EX_CORE_WARN("DrawIndexed...");
		//EX_CORE_WARN("IndexBuffer Count: {0}", vertexArray->GetIndexBuffer()->GetCount());
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
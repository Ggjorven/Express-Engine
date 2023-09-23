#pragma once

#include "Express/Core/Core.hpp"

#include <glad/glad.h>

#include "Express/Renderer/Shader.hpp"

namespace Express
{

	class OpenGLShader : public Shader
	{
	public:
		//OpenGLShader(const std::string& filepath); //TODO
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string fragmentSource);

		void Bind() const override;
		void UnBind() const override;

		void SetUniformInt1(const std::string& name, int value) override;
		void SetUniformFloat3(const std::string& name, const glm::vec3& value) override;
		void SetUniformFloat4(const std::string& name, const glm::vec4& value) override;
		void SetUniformMat4(const std::string& name, const glm::mat4& value) override;

		const std::string& GetName() override { return m_Name; }

	private:
		GLuint Create(const std::string& vertexSource, const std::string& fragmentSource);
		static GLuint Compile(GLenum type, const std::string& data);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

}
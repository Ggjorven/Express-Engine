#include "expch.h"
#include "OpenGLShader.hpp"

#include "Express/Core/Log.hpp"

namespace Express
{

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string fragmentSource)
		: m_Name(name), m_RendererID(0)
	{
		m_RendererID = Create(vertexSource, fragmentSource);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniformInt1(const std::string& name, int value)
	{
		//TODO uniform setting
	}

	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
	{
	}

	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
	{
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
	}

	GLuint OpenGLShader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		GLuint program = glCreateProgram();

		GLuint vertexShader = Compile(GL_VERTEX_SHADER, vertexSource);
		GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSource);

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		//Check for linking failure
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetProgramInfoLog(program, length, &length, &infoLog[0]);

			glDeleteProgram(program);

			EX_CORE_ERROR("{0}", infoLog.data());
			EX_CORE_ASSERT(false, "Shader link failure!");
			return 0;
		}

		return program;
	}

	GLuint OpenGLShader::Compile(GLenum type, const std::string& data)
	{
		GLuint id = glCreateShader(type);

		const char* source = data.c_str();
		glShaderSource(id, 1, &source, nullptr);
		glCompileShader(id);


		//Check for compilation failure
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetShaderInfoLog(id, length, &length, &infoLog[0]);

			glDeleteShader(id);
			return 0;
		}

		return id;
	}
}
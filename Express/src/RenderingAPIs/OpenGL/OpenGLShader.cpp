#include "expch.h"
#include "OpenGLShader.hpp"

#include "Express/Core/Log.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace Express
{

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string fragmentSource)
		: m_Name(name), m_RendererID(0)
	{
		m_RendererID = Create(vertexSource, fragmentSource);
		//EX_CORE_WARN("OpenGLShader m_RendererID: {0}", m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
		//EX_CORE_WARN("OpenGLShader bound.");
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniformInt1(const std::string& name, int value)
	{
		//TODO uniform setting

		GLint location = GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
	{
	}

	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		//Bind();

		GLint location = GetUniformLocation(name);
		glUniform4f(location, value.r, value.g, value.b, value.a); //GL_INVALID_OPERATION without Bind()?
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = GetUniformLocation(name);
		//glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	GLuint OpenGLShader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		GLuint program = glCreateProgram();

		GLuint vertexShader = Compile(GL_VERTEX_SHADER, vertexSource);
		GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSource);

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		glValidateProgram(program);

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

		//Cleanup
		glDeleteShader(m_IntermediateShaderIDs[GL_VERTEX_SHADER]);
		glDeleteShader(m_IntermediateShaderIDs[GL_FRAGMENT_SHADER]);

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

		m_IntermediateShaderIDs[type] = id;
		return id;
	}

	GLint OpenGLShader::GetUniformLocation(const std::string& name)
	{
		//Bind();

		//TODO cache
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		if (location == -1)
			EX_CORE_ASSERT(false, "Uniform does not exist.", name); //Shader probably not bound

		return location;
	}
}
#include "expch.h"
#include "Shader.hpp"

#include "Express/Core/Log.hpp"

#include "Express/Renderer/Renderer.hpp"

#include "RenderingAPIs/OpenGL/OpenGLShader.hpp"

namespace Express
{
	Scope<ShaderLib> ShaderLib::s_Instance = CreateScope<OpenGLShaderLib>();


	ShaderSource Shader::Read(const std::string& filepath)
	{
		enum class ShaderType
		{
			None = -1, Vertex = 0, Fragment = 1
		};

		ShaderSource source;
		ShaderType type = ShaderType::None;

		std::ifstream file(filepath);
		std::string line;
		std::stringstream ss[2];

		while (getline(file, line))
		{

			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::Vertex; continue;
				}
				if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::Fragment; continue;
				}
			}

			ss[(int)type] << line << "\n";
		}

		source.VertexSource = ss[(int)ShaderType::Vertex].str();
		source.FragmentSource = ss[(int)ShaderType::Fragment].str();

		return source;
	}



	Ref<Shader> Shader::Create(const std::string& filepath) //TODO
	{
		EX_CORE_ASSERT(false, "This overload of the Shader::Create function is not supported at the moment")
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EX_CORE_ASSERT(false, "RendererAPI::API::None not supported."); break;
		//case RendererAPI::API::OpenGL: CreateScope<OpenGLShader>(filepath);
		}

		EX_CORE_ASSERT(false, "Not a valid API");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EX_CORE_ASSERT(false, "RendererAPI::API::None not supported."); break;
		case RendererAPI::API::OpenGL: return CreateScope<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		EX_CORE_ASSERT(false, "Not a valid API");
		return nullptr;
	}

	Scope<ShaderLib> ShaderLib::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: EX_CORE_ASSERT(false, "RendererAPI::API::None not supported."); break;
		case RendererAPI::API::OpenGL: return CreateScope<OpenGLShaderLib>();
		}

		EX_CORE_ASSERT(false, "Not a valid API");
		return nullptr;
	}

}
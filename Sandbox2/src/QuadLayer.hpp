#include <Express/Express.hpp>

#include <GL/glew.h>

class QuadLayer : public Express::Layer
{
public:
    QuadLayer()
        : m_VAO(nullptr)
    {
    }

    void OnAttach() override
    {
        Express::RendererCommand::SetClearColour(glm::vec4(0.2f, 0.3f, 0.4f, 1.0f));

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        GLuint indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        // Create Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
        m_VAO = Express::VertexArray::Create();

        Express::Ref<Express::VertexBuffer> VertexBuffer = Express::VertexBuffer::Create(vertices, sizeof(vertices));
        VertexBuffer->SetLayout({ Express::BufferElement(Express::ShaderDataType::Float3, "a_Position", false) });

        Express::Ref<Express::IndexBuffer> IndexBuffer = Express::IndexBuffer::Create(indices, sizeof(indices) / sizeof(GLuint));

        // Bind the VAO first, then bind and set VBO and IBO data
        m_VAO->Bind();

        m_VAO->AddVertexBuffer(VertexBuffer);
        m_VAO->AddIndexBuffer(IndexBuffer);

        //Shader
        const std::string vertexShaderSource = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            void main()
            {
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        const std::string fragmentShaderSource = R"(
            #version 330 core

            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(1.0, 0.5, 0.2, 1.0);
            }
        )";

        m_Shader = Express::Shader::Create("QuadShader", vertexShaderSource, fragmentShaderSource);

    }

    void OnUpdate() override
    {
        m_Shader->Bind();

        m_VAO->Bind();

        //Express::RendererCommand::DrawIndexed(m_VAO);

        Express::Renderer2D::DrawQuad(glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    }

    void OnDetach() override {}
    void OnImGuiRender() override {}
    void OnEvent(Express::Event& e) override {}

private:
    Express::Ref<Express::VertexArray> m_VAO;

    Express::Ref<Express::Shader> m_Shader;
};
#include <Express/Express.hpp>
#include <Express/Core/EntryPoint.hpp>

#include <GL/glew.h>

class MainLayer : public Express::Layer
{
public:
    MainLayer()
        : m_VBO(0), m_EBO(0), m_VAO(0)
    {
        //EX_WARN("Constructor.");
    }

    void OnAttach() override
    {
        //EX_WARN("OnAttach.");
        Express::RendererCommand::SetClearColour(glm::vec4(0.2f, 0.3f, 0.4f, 1.0f));
        // Vertex data for a simple triangle
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // Bottom-left vertex
            0.5f, -0.5f, 0.0f, // Bottom-right vertex
            0.0f,  0.5f, 0.0f  // Top vertex
        };

        // Index data for the triangle
        GLuint indices[] = {
            0, 1, 2 // Triangle indices
        };
        

        // Create Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        // Bind the VAO first, then bind and set VBO and EBO data
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind the VAO
        glBindVertexArray(0);

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

        m_Shader = Express::Shader::Create("TriangleShader", vertexShaderSource, fragmentShaderSource);

    }

    void OnUpdate() override
    {
        //EX_WARN("OnUpdate.");
        // Use the shader program
        m_Shader->Bind();

        /*
        glBegin(GL_POINTS); //starts drawing of points
        glVertex3f(1.0f, 1.0f, 0.0f);//upper-right corner
        glVertex3f(-1.0f, -1.0f, 0.0f);//lower-left corner
        glEnd();//end drawing of points
        */

        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void OnDetach() override
    {
        //EX_WARN("OnDetach.");
        // Clean up
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    // Other event handlers like OnImGuiRender, OnEvent, etc.
    void OnImGuiRender() override {}
    void OnEvent(Express::Event& e) override {}

private:
    GLuint m_VAO, m_VBO, m_EBO;
    Express::Ref<Express::Shader> m_Shader;
};

class Sandbox : public Express::Application
{
public:
    Sandbox()
    {
        // Create and add layers here
        AddLayer(new MainLayer());
    }

    ~Sandbox()
    {
    }
};

Express::Application* Express::CreateApplication()
{
    return new Sandbox();
}

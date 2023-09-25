#include "Express/Express.hpp"

class TriangleApp : public Express::Application
{
public:
    TriangleApp()
    {
    }

    void OnUpdate() override
    {
        // Clear the screen
        Express::RendererCommand::SetClearColour({ 0.0f, 0.0f, 0.0f, 1.0f });
        Express::RendererCommand::Clear();

        // Bind shaders and vertex array
        m_Shader->Bind();
        m_VertexArray->Bind();

        // Draw the triangle
        Express::RendererCommand::DrawIndexed(m_VertexArray);
    }

private:
    Express::Ref<Express::Shader> m_Shader;
    Express::Ref<Express::VertexArray> m_VertexArray;
};

int main()
{
    Express::Log::Init();

    TriangleApp app;
    Express::WindowProperties properties;
    properties.Width = 800;
    properties.Height = 600;
    app.Init(properties);

    // Vertex data for a triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bottom-left
         0.5f, -0.5f, 0.0f, // Bottom-right
         0.0f,  0.5f, 0.0f  // Top-center
    };

    Express::Ref<Express::VertexBuffer> vertexBuffer = Express::VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({
        { Express::ShaderDataType::Float3, "a_Position" }
        });

    Express::Ref<Express::IndexBuffer> indexBuffer = Express::IndexBuffer::Create({ 0, 1, 2 });

    app.Run();

    return 0;
}

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

        m_Texture = Express::Texture2D::Create("assets/images/test.png");
    }

    void OnUpdate() override
    {
        //Express::Renderer2D::DrawQuad(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), m_Degrees, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        //Express::Renderer2D::DrawQuad(glm::vec2(0.5f, 0.5f), glm::vec2(1.0f, 1.0f), m_Degrees, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

        //Express::Renderer2D::DrawQuad(glm::vec2(-0.5f, -0.5f), glm::vec2(1.0f, 1.0f), m_Degrees, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

        Express::Renderer2D::DrawQuad(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), m_Texture);

        m_Degrees += 0.05f;
        EX_WARN("Degrees: {0}", m_Degrees);
    }

    void OnDetach() override {}
    void OnImGuiRender() override {}
    void OnEvent(Express::Event& e) override {}

private:
    Express::Ref<Express::VertexArray> m_VAO;
    Express::Ref<Express::Texture2D> m_Texture;

    float m_Degrees = 0.0f;
};
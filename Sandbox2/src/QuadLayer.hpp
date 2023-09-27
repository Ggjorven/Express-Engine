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

        Express::Renderer2D::DrawQuad(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), m_Degrees, m_Texture);

        m_Degrees += m_Addition;
    }

    void OnDetach() override {}
    void OnImGuiRender() override {}

    void OnEvent(Express::Event& e) override
    {
        Express::EventHandler handler(e);

        handler.Handle<Express::KeyPressedEvent>(EX_BIND_EVENT_FN(QuadLayer::KeyPressEvent));
    }

private:
    bool KeyPressEvent(Express::KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == EX_KEY_UP)
            m_Addition += 0.05f;

        if (e.GetKeyCode() == EX_KEY_DOWN)
            m_Addition -= 0.05f;

        if (e.GetKeyCode() == EX_KEY_SPACE)
        {
            m_Addition *= -1;
            EX_WARN("Mouse position {0}", Express::Input::GetMousePosition().ToString());
        }

        return true;
    }

private:
    Express::Ref<Express::VertexArray> m_VAO;
    Express::Ref<Express::Texture2D> m_Texture;

    float m_Degrees = 0.0f;
    float m_Addition = 0.30f;
};
#include <Express/Express.hpp>

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
        m_CameraController = Express::CreateScope<Express::OrthoGraphicCameraController>(16/9);
    }

    void OnUpdate(Express::TimeStep& ts) override
    {
        m_CameraController->OnUpdate(ts);

        //Rotation
        if (Express::Input::IsKeyPressed(EX_KEY_E))
            m_Degrees += 1.5f * ts;

        if (Express::Input::IsKeyPressed(EX_KEY_Q))
            m_Degrees -= 1.5f * ts;

        //Position
        if (Express::Input::IsKeyPressed(EX_KEY_D))
            m_Position.x += 0.35f * ts;

        if (Express::Input::IsKeyPressed(EX_KEY_A))
            m_Position.x -= 0.35f * ts;

        if (Express::Input::IsKeyPressed(EX_KEY_W))
            m_Position.y += 0.35f * ts;

        if (Express::Input::IsKeyPressed(EX_KEY_S))
            m_Position.y -= 0.35f * ts;
    }
    
    void OnRender() override
    {
        //Rendering
        Express::Renderer2D::DrawQuad(glm::vec2(m_Position.x, m_Position.y), glm::vec2(1.0f, 1.0f), m_Degrees, m_Texture, m_CameraController->GetCamera());
    }

    void OnDetach() override {}
    void OnImGuiRender() override {}

    void OnEvent(Express::Event& e) override
    {
        Express::EventHandler handler(e);

        handler.Handle<Express::KeyPressedEvent>(EX_BIND_EVENT_FN(QuadLayer::KeyPressEvent));

        //Update camera
        m_CameraController->OnEvent(e);
    }

private:
    bool KeyPressEvent(Express::KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == EX_KEY_SPACE)
        {
            m_Degrees += 180;
            //EX_TRACE("Example of Mouse position {0}", Express::Input::GetMousePosition().ToString());
        }

        return true;
    }

private:
    Express::Ref<Express::VertexArray> m_VAO;
    Express::Ref<Express::Texture2D> m_Texture;
    Express::Scope<Express::OrthoGraphicCameraController> m_CameraController;

    float m_Degrees = 0.0f;
    //float m_Addition = 0.00f;

    glm::vec2 m_Position = { 0.0f, 0.0f };
};
#include <Express/Express.hpp>

#include <glm/glm.hpp>

#include <imgui.h>

class QuadLayer : public Express::Layer
{
public:
    QuadLayer()
        : m_VAO(nullptr) //, m_Position(glm::vec2(0.0f, 0.0f))
    {
    }

    void OnAttach() override
    {
        m_Texture = Express::Texture2D::Create("assets/images/test.png");
        m_CameraController = Express::CreateScope<Express::OrthoGraphicCameraController>(Express::Application::Get().GetWindow().GetWidth(), Express::Application::Get().GetWindow().GetHeight());

        m_Position = glm::vec2(0.0f, 0.0f);
    }

    void OnUpdate(Express::TimeStep& ts) override
    {
        Express::RendererCommand::SetClearColour(glm::vec4(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));

        m_CameraController->OnUpdate(ts);

        //Rotation
        if (Express::Input::IsKeyPressed(EX_KEY_E))
            m_Degrees += m_Addition * ts;

        if (Express::Input::IsKeyPressed(EX_KEY_Q))
            m_Degrees -= m_Addition * ts;

        //Position
        if (Express::Input::IsKeyPressed(EX_KEY_D))
            m_Position.x += m_MovementSpeed * ts;

        if (Express::Input::IsKeyPressed(EX_KEY_A))
            m_Position.x -= m_MovementSpeed * ts;

        if (Express::Input::IsKeyPressed(EX_KEY_W))
            m_Position.y += m_MovementSpeed * ts;

        if (Express::Input::IsKeyPressed(EX_KEY_S))
            m_Position.y -= m_MovementSpeed * ts;

        //Logging
        //EX_WARN("Position: x: {0}, y: {1}", m_Position.x, m_Position.y);
    }
    
    void OnRender() override
    {
        //Rendering
        Express::Renderer2D::DrawQuad(glm::vec2(m_Position.x, m_Position.y), glm::vec2(100.0f, 100.0f), m_Degrees, m_Texture, m_CameraController->GetCamera());
        Express::Renderer2D::DrawQuad(glm::vec2(m_SquarePosition[0], m_SquarePosition[1]), glm::vec2(m_SquareSize[0], m_SquareSize[1]), m_CameraController->GetCamera(), glm::vec4(m_SquareColour[0], m_SquareColour[1], m_SquareColour[2], m_SquareColour[3]));
    }

    void OnDetach() override {}
    void OnImGuiRender() override
    {
        //Set Style
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(m_ImGuiTextColour[0], m_ImGuiTextColour[1], m_ImGuiTextColour[2], m_ImGuiTextColour[3]));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(m_ImGuiBackGroundColour[0], m_ImGuiBackGroundColour[1], m_ImGuiBackGroundColour[2], m_ImGuiBackGroundColour[3]));

        //Begin window
        ImGui::Begin("ImGui Window");


        ImGui::Text("Main section");

        ImGui::Spacing();

        ImGui::ColorEdit4("Background Clear Colour", m_ClearColour);

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::ColorEdit4("ImGui Background Colour", m_ImGuiBackGroundColour);
        ImGui::ColorEdit4("ImGui Text Colour", m_ImGuiTextColour);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Textured Square");

        ImGui::Spacing();

        ImGui::DragFloat("Movement speed (WASD)", &m_MovementSpeed, 3.0f, 0.0f, 150.0f);
        ImGui::DragFloat("Rotation addition (Q/E)", &m_Addition, 3.0f, 0.0f, 360.0f);
        ImGui::DragFloat("Rotation", &m_Degrees, 3.0f, 0.0f, 360.0f);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Coloured Square");

        ImGui::Spacing();

        ImGui::ColorEdit4("Colour of the square", m_SquareColour);
        
        ImGui::DragFloat2("Position of the square", m_SquarePosition, 3.f, Express::Application::Get().GetWindow().GetWidth() * -2.0f, Express::Application::Get().GetWindow().GetWidth() * 2.0f);
        ImGui::DragFloat2("Size of the square", m_SquareSize, 3.f, 0.0f, Express::Application::Get().GetWindow().GetWidth() * 2.0f);


        ImGui::End();

        //Remove colour
        ImGui::PopStyleColor(2);
    }

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
        }

        return true;
    }

private:
    Express::Ref<Express::VertexArray> m_VAO;
    Express::Ref<Express::Texture2D> m_Texture;
    Express::Scope<Express::OrthoGraphicCameraController> m_CameraController;

    //Clear Colour
    float m_ClearColour[4] = { 0.2f, 0.3f, 0.2f, 1.0f };

    //ImGui
    float m_ImGuiBackGroundColour[4] = { 0.0f, 0.0f, 0.0f, 0.7f };
    float m_ImGuiTextColour[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

    //Textured square
    float m_MovementSpeed = 75.0f;
    float m_Degrees = 0.0f;
    float m_Addition = 0.0f;

    //Square
    float m_SquareColour[4] = { 0.2f, 0.7f, 0.2f, 1.0f };
    float m_SquarePosition[2] = { 100.0f, 100.0f };
    float m_SquareSize[2] = { 100.0f, 100.0f };

    glm::vec2 m_Position;
};
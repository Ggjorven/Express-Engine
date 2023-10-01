#include "expch.h"
#include "OrthoGraphicCameraController.hpp"

#include "Express/Core/Log.hpp"

#include "Express/Core/Application.hpp"

#include "Express/Events/Input/Input.hpp"
#include "Express/Events/Codes/KeyCodes.hpp"

namespace Express
{

	OrthoGraphicCameraController::OrthoGraphicCameraController(float width, float height, bool rotation)
		: m_Width(width), m_Height(height), m_Rotation(rotation)
	{
		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();
		//float testAspectRatio = (float)Application::Get().GetWindow().GetHeight() / (float)Application::Get().GetWindow().GetWidth();

		m_Camera = CreateRef<OrthoGraphicCamera>(
			-aspectRatio * m_ZoomLevel / 2.0f,
			aspectRatio * m_ZoomLevel / 2.0f,
			-m_ZoomLevel / 2.0f,
			m_ZoomLevel / 2.0f
		);
	}

	void OrthoGraphicCameraController::OnUpdate(TimeStep& ts)
	{
		if (Input::IsKeyPressed(EX_KEY_LEFT))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(EX_KEY_RIGHT))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(EX_KEY_UP))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(EX_KEY_DOWN))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(EX_KEY_KP_4))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			if (Input::IsKeyPressed(EX_KEY_KP_6))
				m_CameraRotation -= m_CameraRotationSpeed * ts;



			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera->SetRotation(m_CameraRotation);
		}

		m_Camera->SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthoGraphicCameraController::OnEvent(Event& e)
	{
		EventHandler dispatcher(e);

		dispatcher.Handle<MouseScrolledEvent>(EX_BIND_EVENT_FN(OrthoGraphicCameraController::OnMouseScrolled));
		dispatcher.Handle<WindowResizeEvent>(EX_BIND_EVENT_FN(OrthoGraphicCameraController::OnWindowResized));
	}

	bool OrthoGraphicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);

		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();

		m_Camera->SetProjection(
			-aspectRatio * m_ZoomLevel / 2.0f,
			aspectRatio * m_ZoomLevel / 2.0f,
			-m_ZoomLevel / 2.0f,
			m_ZoomLevel / 2.0f
		); //TODO fix

		return false;
	}

	bool OrthoGraphicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		float aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		m_Camera->SetProjection(
			-aspectRatio * m_ZoomLevel / 2.0f,
			aspectRatio * m_ZoomLevel / 2.0f,
			-m_ZoomLevel / 2.0f,
			m_ZoomLevel / 2.0f
		);

		return false;
	}
}
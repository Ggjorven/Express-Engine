#pragma once

#include "Express/Core/Core.hpp"

#include "Express/Events/ApplicationEvent.hpp"
#include "Express/Events/Event.hpp"
#include "Express/Events/KeyEvent.hpp"
#include "Express/Events/MouseEvent.hpp"

#include "Express/Renderer/OrthoGraphicCamera.hpp"

#include "Express/Core/TimeStep.hpp"

namespace Express
{

	class OrthoGraphicCameraController
	{
	public:
		OrthoGraphicCameraController(float width, float height, bool rotation = false);

		void OnUpdate(TimeStep& ts);
		void OnEvent(Event& e);

		Ref<OrthoGraphicCamera>& GetCamera() { return m_Camera; }
		const Ref<OrthoGraphicCamera>& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_Width;
		float m_Height;

		float m_ZoomLevel = 1.0f;
		Ref<OrthoGraphicCamera> m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}
#pragma once

#include "Express/Core/Core.hpp"

#include "Express/Events/Input/Input.hpp"

namespace Express
{

	class WindowsInput : public Input
	{
	public:
		WindowsInput() = default;
		virtual ~WindowsInput() = default;

		bool IsKeyPressedImplementation(int keycode) override;
		bool IsMousePressedImplementation(int button) override;

		MousePosition GetMousePositionImplementation() override;

	};

}
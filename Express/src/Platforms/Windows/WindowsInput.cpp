#include "expch.h"
#include "WindowsInput.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Express/Core/Application.hpp"

namespace Express
{
    Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();



    bool WindowsInput::IsKeyPressedImplementation(int keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        int state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMousePressedImplementation(int button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    MousePosition WindowsInput::GetMousePositionImplementation()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { (float)xPos, (float)yPos };
    }

}
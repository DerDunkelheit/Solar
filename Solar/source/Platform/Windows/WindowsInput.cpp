#include "slpch.h"

#include <GLFW/glfw3.h>

#include "Solar/Input.h"
#include "Solar/Application.h"
#include "Solar/Window.h"

namespace Solar
{
    bool Input::IsKeyPressed(int keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const int state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const int state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    static std::pair<float, float> GetMousePosition()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return {xPos, yPos};
    }

    float Input::GetMouseX()
    {
        const auto [x, y] = GetMousePosition();
        return x;
    }

    float Input::GetMouseY()
    {
        const auto [x, y] = GetMousePosition();
        return y;
    }
}

#include "slpch.h"

#ifndef SL_PLATFROM_WINDOWS

#include "WindowsWindow.h"
#include "Solar/Application.h"
#include "Solar/Input.h"

namespace Solar
{
    bool Input::IsKeyPressed(int keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const int state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
}

#endif
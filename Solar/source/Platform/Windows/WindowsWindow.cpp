#include "slpch.h"

#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "WindowsWindow.h"
#include "Solar/Log.h"
#include "Solar/Events/ApplicationEvent.h"
#include "Solar/Events/KeyEvent.h"
#include "Solar/Events/MouseEvent.h"

#include "Platform/OpenGl/OpenGLContext.h"

namespace Solar
{
    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description) 
    {
        SL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        mData.title = props.title;
        mData.width = props.width;
        mData.height = props.height;

        SL_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!s_GLFWInitialized)
        {
            const int success = glfwInit();
            SL_CORE_ASSERT(success);

            glfwSetErrorCallback(GLFWErrorCallback);

            s_GLFWInitialized = true;
        }

        mWindow = glfwCreateWindow(static_cast<int>(props.width), static_cast<int>(props.height), mData.title.c_str(), nullptr, nullptr);

        mContext = new OpenGLContext(mWindow);
        mContext->Init();

        glfwSetWindowUserPointer(mWindow, &mData);
        SetVSync(true);

        //Set GLFW callbacks todo: to method
        glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
        {
                //we could cast void pointer to windowData because we set it to WindowData
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                data.width = width;
                data.height = height;

                WindowResizeEvent engineEvent(width, height);
                data.EventCallback(engineEvent);
        });

        glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
        {
            //we could cast void pointer to windowData because we set it to WindowData
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            WindowCloseEvent engineEvent;
            data.EventCallback(engineEvent);
        });

        glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
                const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        KeyPressedEvent engineEvent(key, -1);
                        data.EventCallback(engineEvent);
                        break;
                    }

                    case GLFW_RELEASE:
                    {
                        KeyReleasedEvent engineEvent(key);
                        data.EventCallback(engineEvent);
                        break;
                    }

                    case GLFW_REPEAT:
                    {
                        //TODO: get repeat count properly
                        KeyPressedEvent engineEvent(key, 1);
                        data.EventCallback(engineEvent);
                        break;
                    }

                default:
                    break;
                }
        });

        glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
        {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        MouseButtonPressedEvent event(button);
                        data.EventCallback(event);
                        break;
                    }

                    case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent event(button);
                        data.EventCallback(event);
                        break;
                    }
                    default:
                        break;
                }
        });

        glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                
                MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
                data.EventCallback(event);
        });

        glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xpos, double ypos)
        {
            const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
                data.EventCallback(event);

        });

        //Set window image.
        std::string imagePath = "Resources/WindowsAssets/WindowIcon.png";
        SL_CORE_ASSERT(std::filesystem::exists(imagePath));
        GLFWimage windowImage;
        windowImage.pixels = stbi_load(imagePath.c_str(), &windowImage.width, &windowImage.height, 0, 4);
        glfwSetWindowIcon(mWindow, 1, &windowImage);
        stbi_image_free(windowImage.pixels);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        mContext->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled);

        mData.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return false;
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(mWindow);
    }

}
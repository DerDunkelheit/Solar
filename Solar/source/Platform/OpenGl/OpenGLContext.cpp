#include "slpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGLContext.h"

namespace Solar
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : mWindowHandle(windowHandle)
    {
        SL_CORE_ASSERT(windowHandle);
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(mWindowHandle);
        const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        SL_CORE_ASSERT(status);

        SL_CORE_INFO("OpenGL Info");
        SL_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
        SL_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        SL_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(mWindowHandle);
    }
}
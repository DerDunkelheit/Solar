#include "slpch.h"

#include <glad/glad.h>

#include "Application.h"
#include "Window.h"
#include "Layers/Layer.h"
#include "Solar/Events/Event.h"
#include "Solar/Events/ApplicationEvent.h"

#include "Renderer/Utils/ShaderUtils.h"

namespace Solar
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        SL_CORE_ASSERT(s_Instance == nullptr)
        s_Instance = this;

        mWindow = std::unique_ptr<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        mImGuiLayer = new ImGuiLayer();
        mImGuiLayer->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        PushOverlay(mImGuiLayer);


        float vertices[] =
        {
            -0.5f, -0.5f, 0.0f,  // bottom left
             0.5f, -0.5f, 0.0f,  // bottom right
             0.5f,  0.5f, 0.0f,  // top right
            -0.5f,  0.5f, 0.0f,  // top left 
             0.0f,  0.5f, 0.0f   // top center
        };

        uint32_t indices[] =
        {
            // square 
            //0, 1, 3,
            //1, 3, 2

            // triangle
            0, 1, 4
        };

        //vertex buffer object
        uint32_t VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        // vertex can have a several attributes, for instacne positions, color, normal, etc.
        // o is an attribute index (in this case positions)
        // 3 is how many elements there are per attribute(x , y, z)
        // GL_FLOAT is a type of attribute
        // GL_FALSE for normalize (could be useful for colors)
        // (sizeof(float) * 3) is a stride, which means the ending positions.
        // 0 is offset of attribute, imagine if we have an attribute after positions and if we wanna use it, we have to set offses for it. (if would be sizeof(float) * x)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        ShaderUtils::ShaderData shaderData = ShaderUtils::ParseShader("Resources/Shaders/Basic.shader");
        uint32_t shader = ShaderUtils::CreateShader(shaderData.VertexShader, shaderData.FragmentShader);
        glUseProgram(shader);

        //After useProgram. We can get the shader variables and modify them in render loop.
        int location = glGetUniformLocation(shader, "u_Color");
        glUniform4f(location, 0.4f, 0.2f, 0.8f, 1.0f);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(mRed, mGreen, mBlue, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

            for (Layer* layer : mLayerStack)
            {
                layer->OnUpdate();
            }

            //TODO: to separate thread
            mImGuiLayer->Begin();
            for (Layer* layer : mLayerStack)
            {
                layer->OnImGuiRender();
            }
            mImGuiLayer->End();
            
            mWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResized));
        dispatcher.Dispatch<ColorChangedEvent>(BIND_EVENT_FN(Application::OnColorChanged));
        
        for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
        {
            (*--it)->OnEvent(event);
            if (event.Handled) break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        mLayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        mLayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClosed(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResized(WindowResizeEvent& event)
    {
        glViewport(0, 0, event.GetWidth(), event.GetHeight());
        return true;
    }

    bool Application::OnColorChanged(ColorChangedEvent& event)
    {
        mRed = event.GetRedValue();
        mGreen = event.GetGreenValue();
        mBlue = event.GetBlueValue();


        return true;
    }
}
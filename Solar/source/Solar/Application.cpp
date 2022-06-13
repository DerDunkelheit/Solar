#include "slpch.h"

#include <glad/glad.h>

#include "Application.h"
#include "Window.h"
#include "Layers/Layer.h"
#include "Solar/Events/Event.h"
#include "Solar/Events/ImGuiEvents.h"
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

        mVertexArray.reset(VertexArray::Create());
        mVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        mElementBuffer.reset(ElementBuffer::Create(indices, sizeof(indices)));

        const BufferLayout layout =
        {
            {ShaderDataType::Float3, "a_Position"}
        };

        mVertexBuffer->SetLayout(layout);
        mVertexArray->AddVertexBuffer(mVertexBuffer);


        //mSquareVertexArray.reset(VertexArray::Create());
        //std::shared_ptr<VertexBuffer> squareVB = std::make_shared<VertexBuffer>();

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

            mVertexArray->Bind();
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
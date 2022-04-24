#include "slpch.h"

#include <glad/glad.h>

#include "Application.h"
#include "Window.h"
#include "Layers/Layer.h"
#include "Solar/Events/Event.h"
#include "Solar/Events/ApplicationEvent.h"
#include "Solar/Window.h"

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
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : mLayerStack)
            {
                layer->OnUpdate();
            }
            
            mWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
        
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
}
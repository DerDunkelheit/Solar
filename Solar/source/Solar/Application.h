#pragma once

#include "Core.h"
#include "Layers/LayerStack.h"

namespace Solar
{
    class Event;
    class WindowCloseEvent;
    class Window;
    class Layer;

    class SOLAR_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        bool OnWindowClosed(WindowCloseEvent& event);

        std::unique_ptr<Window> mWindow;
        bool m_Running = true;
        LayerStack mLayerStack;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}


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

        static Application& Get()
        {
            return *s_Instance;
        }

        Window& GetWindow() const { return *mWindow; }
    private:
        bool OnWindowClosed(WindowCloseEvent& event);

    private:
        static Application* s_Instance;

        std::unique_ptr<Window> mWindow;
        bool m_Running = true;
        LayerStack mLayerStack;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}


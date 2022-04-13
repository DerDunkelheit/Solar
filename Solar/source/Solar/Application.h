#pragma once

#include "Core.h"

namespace Solar
{
    class Event;
    class WindowCloseEvent;
    class Window;

    class SOLAR_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& event);
    private:
        bool OnWindowClosed(WindowCloseEvent& event);

        std::unique_ptr<Window> mWindow;
        bool m_Running = true;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}


#pragma once

#include "slpch.h"

#include "Solar/Core.h"
#include "Solar/Events/Event.h"

namespace Solar
{
    struct WindowProps
    {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& _title = "Solar Engine", unsigned int _widht = 1280, unsigned int _height = 720)
            : width(_widht), height(_height), title(_title)
        {

        }
    };

    class SOLAR_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {};

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        //Implementation in a platform specific file.
        static Window* Create(const WindowProps& props = WindowProps());
    };
}
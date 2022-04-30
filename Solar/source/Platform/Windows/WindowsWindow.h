#pragma once

#include <GLFW/glfw3.h>

#include "Solar/Window.h"

namespace Solar
{
    class WindowsWindow : public Window
    {
    public:

        WindowsWindow(const WindowProps& props);

        virtual ~WindowsWindow() override;

        void OnUpdate() override;

        virtual unsigned int GetWidth() const override { return mData.width; };
        virtual unsigned int GetHeight() const override { return mData.height; };

        virtual void SetEventCallback(const EventCallbackFn& callback) override { mData.EventCallback = callback; }
        virtual void SetVSync(bool enabled) override;
        virtual bool IsVSync() const override;
        
        virtual void* GetNativeWindow() const override { return mWindow; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        GLFWwindow* mWindow;

        struct WindowData
        {
            std::string title;
            unsigned int width;
            unsigned int height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData mData;
    };
}
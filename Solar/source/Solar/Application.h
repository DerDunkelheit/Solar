#pragma once

#include "Core.h"
#include "Layers/LayerStack.h"
#include "Solar/Layers/ImGui/ImGuiLayer.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace Solar
{
    class Event;
    class WindowCloseEvent;
    class WindowResizeEvent;
    class ColorChangedEvent;
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
        bool OnWindowResized(WindowResizeEvent& event);
        bool OnColorChanged(ColorChangedEvent& event);

    private:
        static Application* s_Instance;

        std::unique_ptr<Window> mWindow;
        ImGuiLayer* mImGuiLayer;
        bool m_Running = true;
        LayerStack mLayerStack;


        //Rendering
        std::shared_ptr<VertexBuffer> mVertexBuffer;
        std::shared_ptr<ElementBuffer> mElementBuffer;
        std::shared_ptr<VertexArray> mVertexArray;

        //for testing
        std::shared_ptr<VertexArray> mSquareVertexArray;


        //TODO: create a proper container for this
        float mRed = 0.09f;
        float mGreen = 0.09f;
        float mBlue = 0.09f;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}


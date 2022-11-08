#pragma once

#include <glm/vec4.hpp>

#include "Core.h"
#include "Layers/LayerStack.h"
#include "Solar/Layers/ImGui/ImGuiLayer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

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
        std::shared_ptr<VertexArray> mVAO;
        std::shared_ptr<Shader> shader;

        //for testing
        std::shared_ptr<VertexArray> mVAO_sqr;
        std::shared_ptr<Shader> shader_sqr;
        std::shared_ptr<Shader> colorChangeShader;
        
        glm::vec4 mBackgroundColor;
        glm::vec4 mShaderColor;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}


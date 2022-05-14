#include <Solar.h>

#include "imgui.h"

class ExampleLayer : public Solar::Layer
{
public:
    ExampleLayer()
        : Layer("Example") {}

    virtual void OnUpdate() override
    {
        
    }

    virtual void OnImGuiRender() override
    {
        static bool showTestWindow = false;
        ImGui::Begin("SandBox window", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking);
        ImGui::Checkbox("ShowWindow", &showTestWindow);
        ImGui::End();
        
        if(showTestWindow)
        {
            ImGui::Begin("Test", &showTestWindow);
            ImGui::Text("Render from Sandbox layer");
            ImGui::End();
        }
    }

    virtual void OnEvent(Solar::Event& event) override
    {
        
    }
};

class Sandbox : public Solar::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer);
    }

    virtual ~Sandbox() override
    {

    }
};

Solar::Application* Solar::CreateApplication()
{
    return new Sandbox();
}
#include <Solar.h>


class ExampleLayer : public Solar::Layer
{
public:
    ExampleLayer()
        : Layer("Example") {}

    virtual void OnUpdate() override
    {
        
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
        PushOverlay(new Solar::ImGuiLayer);
    }

    virtual ~Sandbox() override
    {

    }
};

Solar::Application* Solar::CreateApplication()
{
    return new Sandbox();
}
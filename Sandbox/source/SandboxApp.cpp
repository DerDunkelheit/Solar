#include <Solar.h>

class ExampleLayer : public Solar::Layer
{
public:
    ExampleLayer()
        : Layer("Example") {}

    virtual void OnUpdate() override
    {
        SL_INFO("ExampleLayer::OnUpdate");
    }

    virtual void OnEvent(Solar::Event& event) override
    {
        SL_TRACE("{0}", event);
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
#include <Solar.h>

class Sandbox : public Solar::Application
{
public:
    Sandbox()
    {

    }

    virtual ~Sandbox() override
    {

    }
};

Solar::Application* Solar::CreateApplication()
{
    return new Sandbox();
}
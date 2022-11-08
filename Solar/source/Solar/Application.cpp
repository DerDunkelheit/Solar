#include "slpch.h"

#include "Application.h"
#include "Window.h"
#include "Layers/Layer.h"
#include "Solar/Events/Event.h"
#include "Solar/Events/ImGuiEvents.h"
#include "Solar/Events/ApplicationEvent.h"
#include "Renderer/Utils/ShaderUtils.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

namespace Solar
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        SL_CORE_ASSERT(s_Instance == nullptr)
        s_Instance = this;

        mWindow = std::unique_ptr<Window>(Window::Create());
        mWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        mImGuiLayer = new ImGuiLayer();
        mImGuiLayer->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        PushOverlay(mImGuiLayer);


        float vertices[] =
        {
            -0.5f, -0.5f, 0.0f,  // bottom left
             0.5f, -0.5f, 0.0f,  // bottom right
             0.5f,  0.5f, 0.0f,  // top right
            -0.5f,  0.5f, 0.0f,  // top left 
             0.0f,  0.5f, 0.0f   // top center
        };

        uint32_t indices[] =
        {
            // square 
            //0, 1, 3,
            //1, 3, 2

            // triangle
            0, 1, 4
        };

        mVAO.reset(VertexArray::Create());
        std::shared_ptr<VertexBuffer> VBO;
        std::shared_ptr<ElementBuffer> EBO;
        VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        EBO.reset(ElementBuffer::Create(indices, sizeof(indices)));

        const BufferLayout layout =
        {
            {ShaderDataType::Float3, "a_Position"}
        };

        VBO->SetLayout(layout);
        mVAO->AddVertexBuffer(VBO);


        // For testing -----------------------------------------------------------------------
        mVAO_sqr.reset(VertexArray::Create());

        float verticesSqr[] =
        {
            -0.75f, -0.75f, 0.0f,  // bottom left
             0.75f, -0.75f, 0.0f,  // bottom right
             0.75f,  0.75f, 0.0f,  // top right
            -0.75f,  0.75f, 0.0f,  // top left 
             0.0f,   0.5f,  0.0f   // top center
        };

        uint32_t indicesSqr[] =
        {
            // square 
            0, 1, 3,
            1, 3, 2
        };
        
        std::shared_ptr<VertexBuffer> VBO_sqr;
        VBO_sqr.reset(VertexBuffer::Create(verticesSqr, sizeof(verticesSqr)));
        
        const BufferLayout layoutSqr =
        {
            {ShaderDataType::Float3, "a_Position"}
        };

        VBO_sqr->SetLayout(layout);
        mVAO_sqr->AddVertexBuffer(VBO_sqr);

        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(indicesSqr, sizeof(indicesSqr) / sizeof(uint32_t)));
        mVAO_sqr->SetIndexBuffer(squareIB);
        
        //------------------------------------------------------------------------------------
        
        shader.reset(new Shader(ShaderUtils::ParseShader("Resources/Shaders/Basic.shader")));
        shader->Bind();

        shader_sqr.reset(new Shader(ShaderUtils::ParseShader("Resources/Shaders/BlueShader.shader")));
        shader_sqr->Bind();

        colorChangeShader.reset(new Shader(ShaderUtils::ParseShader("Resources/Shaders/ColorChange.shader")));
        colorChangeShader->Bind();

        //After useProgram. We can get the shader variables and modify them in render loop.
        int location = shader->GetLocation("u_Color");

        mBackgroundColor.r = 0.09f;
        mBackgroundColor.g = 0.09f;
        mBackgroundColor.b = 0.09f;

        mShaderColor.r = 0.3f;
        mShaderColor.g = 0.04f;
        mShaderColor.b = 0.04f;
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            RenderCommand::SetClearColor(mBackgroundColor);
            RenderCommand::Clear();

            Renderer::BeginScene();

            //For testing ----------------------------------------------------------------
            colorChangeShader->Bind();
            colorChangeShader->SetColor("ourColor", mShaderColor);
            Renderer::Submit(mVAO_sqr);
            // ---------------------------------------------------------------------------

            shader->Bind();
            Renderer::SubmitElementBuffer(mVAO, 3);
            
            Renderer::EndScene();

            for (Layer* layer : mLayerStack)
            {
                layer->OnUpdate();
            }

            //TODO: to separate thread
            mImGuiLayer->Begin();
            for (Layer* layer : mLayerStack)
            {
                layer->OnImGuiRender();
            }
            mImGuiLayer->End();
            
            mWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResized));
        dispatcher.Dispatch<ColorChangedEvent>(BIND_EVENT_FN(Application::OnColorChanged));

        for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
        {
            (*--it)->OnEvent(event);
            if (event.Handled) break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        mLayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        mLayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClosed(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResized(WindowResizeEvent& event)
    {
        RenderCommand::UpdateViewportSize(event.GetWidth(), event.GetHeight());
        return true;
    }

    bool Application::OnColorChanged(ColorChangedEvent& event)
    {
        if(event.GetPropertyName().has_value())
        {
            if (event.GetPropertyName().value() == "shaderColor")
            {
                mShaderColor = event.GetColor();
            }
        }
        else
        {
            mBackgroundColor = event.GetColor();
        }

        return true;
    }
}
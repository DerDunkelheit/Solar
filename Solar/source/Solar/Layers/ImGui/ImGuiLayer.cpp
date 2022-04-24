#include "slpch.h"

#include "imgui.h"
#include "Platform/OpenGl/ImGuiOpenGLRenderer.h"
#include "Platform/OpenGl/ImGuiGLFWRenderer.h"
#include <glad/glad.h>

#include "ImGuiLayer.h"
#include "Solar/Application.h"
#include "Solar/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Solar
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable docking

        const char* glsl_version = "#version 130";
        Application& app = Application::Get();
        //VERY BAAAAAAAAAAD
        WindowsWindow& window = static_cast<WindowsWindow&>(app.GetWindow());
        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(window.GetNativeWindow()), true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        ImGui::StyleColorsDark();
    }

    void ImGuiLayer::OnDetach()
    {
        
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = mTime > 0.0 ? (time - mTime) : (1.0f / 60.0f);
        mTime = time;

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    void ImGuiLayer::OnEvent(Event& event)
    {
        SL_CORE_TRACE("{0}", event);
    }
}

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
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable viewports

        const char* glsl_version = "#version 130";
        const Application& app = Application::Get();
        
        //TODO: create a platform specific wrapper for getting windows 
        ImGui_ImplGlfw_InitForOpenGL(static_cast<WindowsWindow&>(app.GetWindow()).GetNativeWindow(), true);
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
        const Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = static_cast<float>(glfwGetTime());
        io.DeltaTime = mTime > 0.0 ? (time - mTime) : (1.0f / 60.0f);
        mTime = time;

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::OnEvent(Event& event)
    {
        
    }
}

#include "slpch.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGuiLayer.h"
#include "Solar/Application.h"
#include "Solar/Window.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Solar/Events/ImGuiEvents.h"

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
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable viewports

        const char* glsl_version = "#version 410";
        const Application& app = Application::Get();

        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        
        //TODO: create a platform specific wrapper for getting windows 
        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow()), true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::OnImGuiRender()
    {
        ImGuiIO& io = ImGui::GetIO();
        float time = static_cast<float>(glfwGetTime());
        io.DeltaTime = mTime > 0.0 ? (time - mTime) : (1.0f / 60.0f);
        mTime = time;

        ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        static float col1[3] = { 0.09f, 0.09f, 0.09f };
        if (ImGui::ColorEdit3("color 1", col1))
        {
            if (mEventCallback != nullptr)
            {
                ColorChangedEvent event(col1[0], col1[1], col1[2]);
                mEventCallback(event);
            }
        }

        ImGui::Separator();
        static bool showDemoWindow = false;
        ImGui::Checkbox("ShowDemoWindow", &showDemoWindow);
        if (showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);

        ImGui::End();
    }
    
   void ImGuiLayer::End()
   {
        ImGuiIO& io = ImGui::GetIO();
        const Application& app = Application::Get();
        io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

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


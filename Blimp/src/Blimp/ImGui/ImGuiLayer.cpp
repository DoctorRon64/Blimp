#include "ImGuiLayer.h"

#include "Platform/OpenGL/imGui.h"
#include "Blimp/Application.h"

namespace Blimp
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer") {
    }

    ImGuiLayer::~ImGuiLayer() = default;

    void ImGuiLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        m_Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        // TODO set to own keymapping IMPORTANT: this sets up input callbacks, key mapping, etc.
        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        
        // Use a version that matches your created GL context.
        // For Win+Linux, 330 is the safest default.
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiIO& io = ImGui::GetIO();

        // Prefer framebuffer size (handles HiDPI correctly)
        int fbw = 0, fbh = 0;
        glfwGetFramebufferSize(m_Window, &fbw, &fbh);
        io.DisplaySize = ImVec2((float)fbw, (float)fbh);

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event &event){
        // With imgui_impl_glfw + install_callbacks=true,
        // you typically don't need to forward events manually.
        // Later you can add "block events when ImGui wants capture" here.
        (void)event;
    }

} // namespace Blimp

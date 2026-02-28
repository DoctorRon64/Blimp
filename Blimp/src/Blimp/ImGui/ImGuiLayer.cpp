#include "pch.h"
#include "ImGuiLayer.h"

#include "Blimp/Application.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

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
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();
        m_Window = static_cast<::GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        // Backend callback installation keeps ImGui input state in sync.
        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
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

        if (m_ShowDebugWindow)
        {
            ImGui::Begin("ImGuiLayer");
            ImGui::Text("ImGui backend active");
            ImGui::Text("Framebuffer: %d x %d", fbw, fbh);
            ImGui::Checkbox("Block Events", &m_BlockEvents);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event &event){
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowResizeEvent>(BLIMP_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));

        if (!m_BlockEvents)
            return;

        const ImGuiIO& io = ImGui::GetIO();
        const bool mouseEvent = event.IsInCategory(EventCategoryMouse) || event.IsInCategory(EventCategoryMouseButton);
        const bool keyboardEvent = event.IsInCategory(EventCategoryKeyboard);
        event.Handled |= (mouseEvent && io.WantCaptureMouse) || (keyboardEvent && io.WantCaptureKeyboard);
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
            return false;

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
        return false;
    }
} // namespace Blimp

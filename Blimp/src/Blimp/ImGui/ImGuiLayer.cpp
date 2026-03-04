#include "pch.h"
#include "ImGuiLayer.h"

#include "Blimp/Application.h"
#include "ImGuiBuild.h"
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
#ifdef IMGUI_HAS_DOCK
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#endif
#ifdef IMGUI_HAS_VIEWPORT
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
#endif

        ImGui::StyleColorsDark();
#ifdef IMGUI_HAS_VIEWPORT
        // Recommended by Dear ImGui when viewports are enabled.
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
#endif
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

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO& io = ImGui::GetIO();

        // Keep ImGui display size aligned with the actual framebuffer (HiDPI-safe).
        int fbw = 0, fbh = 0;
        glfwGetFramebufferSize(m_Window, &fbw, &fbh);
        io.DisplaySize = ImVec2((float)fbw, (float)fbh);

        // Render the main viewport draw data.
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Multi-viewport APIs are only available on specific ImGui builds.
#ifdef IMGUI_HAS_VIEWPORT
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
#endif
    }

    void ImGuiLayer::OnImGuiRender() {
        static bool showDemoWindow = false;

#ifdef IMGUI_HAS_DOCK
        ImGuiWindowFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
        windowFlags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("BlimpDockspace", nullptr, windowFlags);
        ImGui::PopStyleVar(3);

        ImGuiID dockspaceId = ImGui::GetID("BlimpDockspaceRoot");
        ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);
        ImGui::End();
#endif

        if (m_ShowDebugWindow) {
            ImGuiIO& io = ImGui::GetIO();
            ImGui::Begin("Blimp ImGui");
#ifdef IMGUI_HAS_DOCK
            ImGui::Text("Docking: enabled");
#else
            ImGui::Text("Docking: unavailable in this ImGui build");
#endif
#ifdef IMGUI_HAS_VIEWPORT
            ImGui::Text("External windows: enabled");
#else
            ImGui::Text("External windows: unavailable in this ImGui build");
#endif
            ImGui::Text("Display: %d x %d", (int)io.DisplaySize.x, (int)io.DisplaySize.y);
            ImGui::Checkbox("Block Events", &m_BlockEvents);
            ImGui::Checkbox("Show Demo Window", &showDemoWindow);
            ImGui::End();
        }

        if (showDemoWindow) {
            ImGui::ShowDemoWindow(&showDemoWindow);
        }
    }

    void ImGuiLayer::OnEvent(Event& event) {
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

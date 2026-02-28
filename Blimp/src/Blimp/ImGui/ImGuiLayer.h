#pragma once

#include "Blimp/Layer.h"
#include "Blimp/Events/ApplicationEvent.h"
#include "Blimp/Events/Event.h"

struct GLFWwindow;

namespace Blimp
{
    class BLIMP_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event &event) override;

        void SetBlockEvents(bool block) { m_BlockEvents = block; }
        bool IsBlockingEvents() const { return m_BlockEvents; }
        void SetShowDebugWindow(bool show) { m_ShowDebugWindow = show; }
 
    private:
        bool OnWindowResizeEvent(WindowResizeEvent& e);
    private:
        ::GLFWwindow* m_Window = nullptr;
        bool m_BlockEvents = true;
        bool m_ShowDebugWindow = true;
    };
} // namespace Blimp

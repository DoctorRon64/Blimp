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

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event& event) override;
        virtual void OnImGuiRender() override;

        void SetBlockEvents(bool block) { m_BlockEvents = block; }
        bool IsBlockingEvents() const { return m_BlockEvents; }
        void SetShowDebugWindow(bool show) { m_ShowDebugWindow = show; }

        void Begin();
        void End();

    private:
        bool OnWindowResizeEvent(WindowResizeEvent& e);

    private:
        GLFWwindow* m_Window = nullptr;
        bool m_BlockEvents = true;
        bool m_ShowDebugWindow = true;
    };
} // namespace Blimp

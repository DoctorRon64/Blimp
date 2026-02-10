#pragma once

#include "Blimp/Layer.h"
#include <GLFW/glfw3.h>

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
 
    private:
        GLFWwindow* m_Window = nullptr;

    };
} // namespace Blimp

#include "pch.h"
#include "LinuxInput.h"

#include "Blimp/Application.h"
#include <GLFW/glfw3.h>

namespace Blimp {
    namespace {
        static GLFWwindow* GetGLFWWindow() {
            return static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        }
    }

    bool LinuxInput::IsKeyPressedImplementation(int keyCode) const {
        auto* window = GetGLFWWindow();
        int state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonPressedImplementation(int button) const {
        auto* window = GetGLFWWindow();
        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> LinuxInput::GetMousePosImplementation() const {
        auto* window = GetGLFWWindow();
        double xPos = 0.0;
        double yPos = 0.0;
        glfwGetCursorPos(window, &xPos, &yPos);
        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

    float LinuxInput::GetMouseXImplementation() const {
        auto [x, y] = GetMousePosImplementation();
        (void)y;
        return x;
    }

    float LinuxInput::GetMouseYImplementation() const {
        auto [x, y] = GetMousePosImplementation();
        (void)x;
        return y;
    }
}

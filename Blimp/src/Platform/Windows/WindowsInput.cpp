#include "pch.h"
#include "WindowsInput.h"

#include "Blimp/Application.h"
#include <GLFW/glfw3.h>

namespace Blimp {
    namespace {
        static GLFWwindow* GetGLFWWindow() {
            return static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        }
    }

    bool WindowsInput::IsKeyPressedImplementation(int keycode) const {
        auto* window = GetGLFWWindow();
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImplementation(int button) const {
        auto* window = GetGLFWWindow();
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePosImplementation() const {
        auto* window = GetGLFWWindow();
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { static_cast<float>(xpos), static_cast<float>(ypos) };
    }

    float WindowsInput::GetMouseXImplementation() const {
        auto [x, y] = GetMousePosImplementation();
        (void)y;
        return x;
    }

    float WindowsInput::GetMouseYImplementation() const {
        auto [x, y] = GetMousePosImplementation();
        (void)x;
        return y;
    }
}

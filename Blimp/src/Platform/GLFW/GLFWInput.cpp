#include "pch.h"
#include "GLFWInput.h"

#include "Blimp/Application.h"
#include <GLFW/glfw3.h>

namespace Blimp {
	namespace {
		static GLFWwindow* GetGLFWWindow() {
			return static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		}
	}

	bool GLFWInput::IsKeyPressedImplementation(int keyCode) const {
		auto* window = GetGLFWWindow();
		const int state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GLFWInput::IsMouseButtonPressedImplementation(int button) const {
		auto* window = GetGLFWWindow();
		const int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> GLFWInput::GetMousePosImplementation() const {
		auto* window = GetGLFWWindow();
		double xPos = 0.0;
		double yPos = 0.0;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { static_cast<float>(xPos), static_cast<float>(yPos) };
	}

	float GLFWInput::GetMouseXImplementation() const {
		auto [x, y] = GetMousePosImplementation();
		(void)y;
		return x;
	}

	float GLFWInput::GetMouseYImplementation() const {
		auto [x, y] = GetMousePosImplementation();
		(void)x;
		return y;
	}
}

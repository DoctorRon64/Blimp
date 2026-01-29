#include "pch.h"
#include "LinuxWindow.h"

namespace Blimp {
	static bool GLFW_Initialized = false;

	LinuxWindow::LinuxWindow(const WindowProperties& properties) {
		Init(properties);
	}

	LinuxWindow::~LinuxWindow() {
		Terminate();
	}

	void LinuxWindow::Init(const WindowProperties& properties) {
		Data_.Title = properties.Title;
		Data_.Width = properties.Width;
		Data_.Height = properties.Height;

		BLIMP_CORE_INFO("Creating window {0} ({1}, {2})", properties.Title, properties.Width, properties.Height);

		if (!GLFW_Initialized) {
			int success = glfwInit();
			BLIMP_CORE_ASSERT(success, "Could not init GLFW!");

			GLFW_Initialized = true;
		}

		m_Window = glfwCreateWindow(static_cast<int>(properties.Width), static_cast<int>(properties.Height), Data_.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &Data_);
		SetVSync(true);
	}

	void LinuxWindow::Terminate() {
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}

	void LinuxWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void LinuxWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		Data_.VSync = enabled;
	}

	bool LinuxWindow::IsVSync() const {
		return Data_.VSync;
	}
}

#include "pch.h"
#include "LinuxWindow.h"

#include "Blimp/Events/ApplicationEvent.h"
#include "Blimp/Events/KeyEvent.h"
#include "Blimp/Events/MouseEvent.h"

#include <glad/glad.h>

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
		BLIMP_CORE_ASSERT(m_Window, "Could not create GLFW window!");
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BLIMP_CORE_ASSERT(status, "Cannot initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &Data_);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = static_cast<unsigned int>(width);
			data.Height = static_cast<unsigned int>(height);

			WindowResizeEvent event(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			(void)scancode;
			(void)mods;

			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, false);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, true);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(static_cast<int>(keycode));
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			(void)mods;

			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			data.EventCallback(event);
		});
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

	void* LinuxWindow::GetNativeWindow() const
	{
		return m_Window; // m_Window is GLFWwindow*
	}
}

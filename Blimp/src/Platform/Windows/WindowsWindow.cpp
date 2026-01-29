#include "pch.h"
#include "WindowsWindow.h"

#include "Blimp/Events/ApplicationEvent.h"
#include "Blimp/Events/MouseEvent.h"
#include "Blimp/Events/KeyEvent.h"

namespace Blimp {
	static bool GLFW_Initialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		BLIMP_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	} 
	
	WindowsWindow::WindowsWindow(const WindowProperties& properties) {
		Init(properties);
	}

	WindowsWindow::~WindowsWindow() {
		Terminate();
	}

	void WindowsWindow::Init(const WindowProperties& properties) {
		Data_.Title = properties.Title;
		Data_.Width = properties.Width;
		Data_.Height = properties.Height;

		BLIMP_CORE_INFO("Creating window {0} ({1}, {2})", properties.Title, properties.Width, properties.Height);

		if(!GLFW_Initialized) {
			int success = glfwInit();
			BLIMP_CORE_ASSERT(success, "Could not init GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFW_Initialized = true;
		}

		m_Window = glfwCreateWindow(static_cast<int>(properties.Width), static_cast<int>(properties.Height), Data_.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &Data_);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch(action) {
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

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch(action) {
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

			MouseScrolledEvent event((float) xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

		//TODO add icon to game engine after we have asset loading!
		//GLFWimage images[1];
		//glfwSetWindowIcon(m_Window, 2, images);
	}

	void WindowsWindow::Terminate() {
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if(enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		Data_.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return Data_.VSync;
	}
}

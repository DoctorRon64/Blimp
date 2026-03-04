#include "pch.h"
#include "GLFWWindow.h"

#include "Blimp/Events/ApplicationEvent.h"
#include "Blimp/Events/KeyEvent.h"
#include "Blimp/Events/MouseEvent.h"

namespace Blimp {
	static bool GLFW_Initialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		BLIMP_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	GLFWWindow::GLFWWindow(const WindowProperties& properties) {
		Init(properties);
	}

	GLFWWindow::~GLFWWindow() {
		Terminate();
	}

	void GLFWWindow::Init(const WindowProperties& properties) {
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		BLIMP_CORE_INFO("Creating window {0} ({1}, {2})", properties.Title, properties.Width, properties.Height);

		if(!GLFW_Initialized) {
			//TODO glfwTerminate on system shutdown
			int success = glfwInit();
			BLIMP_CORE_ASSERT(success, "Could not init GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFW_Initialized = true;
		}

		m_Window = glfwCreateWindow(static_cast<int>(properties.Width), static_cast<int>(properties.Height), m_Data.Title.c_str(), nullptr, nullptr);
		BLIMP_CORE_ASSERT(m_Window, "Could not create GLFW window!");

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
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

			switch(action) {
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, false);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
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

			switch(action) {
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
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

	void GLFWWindow::Terminate() {
		m_Context.reset();

		if(m_Window) {
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
		}
	}

	void GLFWWindow::OnUpdate() {
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void GLFWWindow::SetVSync(bool enabled) {
		m_Context->SetVSync(enabled);
	}

	bool GLFWWindow::IsVSync() const {
		return m_Context->IsVSync();
	}

	void* GLFWWindow::GetNativeWindow() const {
		return m_Window;
	}
}

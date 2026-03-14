#include "pch.h"
#include "OpenGLContext.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace Blimp {
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window) {
		BLIMP_CORE_ASSERT(window, "Window handle is null");
	}
	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		const int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if(gladStatus == 0) {
			BLIMP_CORE_ERROR("Cannot initialize Glad!");
			BLIMP_CORE_ASSERT(false, "Cannot initialize Glad!");
			throw std::runtime_error("Cannot initialize Glad!");
		}

		BLIMP_CORE_INFO("OpenGL Info");
		const char* vendor   = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		const char* version  = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		BLIMP_CORE_INFO("Vendor: {}", vendor ? vendor : "<null>");
		BLIMP_CORE_INFO("Renderer: {}", renderer ? renderer : "<null>");
		BLIMP_CORE_INFO("Version: {}", version ? version : "<null>");
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::SetVSync(bool enabled) {
		glfwSwapInterval(enabled ? 1 : 0);
		m_VSync = enabled;
	}

	bool OpenGLContext::IsVSync() const {
		return m_VSync;
	}
}

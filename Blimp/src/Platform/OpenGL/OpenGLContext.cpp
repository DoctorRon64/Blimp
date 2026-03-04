#include "pch.h"
#include "OpenGLContext.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

namespace Blimp {
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window) {
		BLIMP_CORE_ASSERT(window, "Window handle is null");
	}
	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BLIMP_CORE_ASSERT(status, "Cannot initialize Glad!");
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

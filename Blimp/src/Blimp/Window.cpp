#include "pch.h"
#include "Window.h"

#include "Platform/GLFW/GLFWWindow.h"

namespace Blimp {
	Window* Window::Create(const WindowProperties& properties) {
	#if defined(BLIMP_PLATFORM_WINDOWS) || defined(BLIMP_PLATFORM_LINUX)
		return new GLFWWindow(properties);
	#else
		BLIMP_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
}

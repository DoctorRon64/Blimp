#include "pch.h"
#include "Window.h"

#if defined(BLIMP_PLATFORM_WINDOWS)
#include "Platform/Windows/WindowsWindow.h"
#elif defined(BLIMP_PLATFORM_LINUX)
#include "Platform/Linux/LinuxWindow.h"
#endif

namespace Blimp {
	Window* Window::Create(const WindowProperties& properties) {
#if defined(BLIMP_PLATFORM_WINDOWS)
		return new WindowsWindow(properties);
#elif defined(BLIMP_PLATFORM_LINUX)
		return new LinuxWindow(properties);
#else
		BLIMP_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}

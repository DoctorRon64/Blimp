#include "pch.h"
#include "GraphicsContext.h"

#if defined(BLIMP_PLATFORM_WINDOWS) || defined(BLIMP_PLATFORM_LINUX)
#include "Platform/OpenGL/OpenGLContext.h"
#include <GLFW/glfw3.h>
#endif

namespace Blimp {
	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* windowHandle) {
#if defined(BLIMP_PLATFORM_WINDOWS) || defined(BLIMP_PLATFORM_LINUX)
		return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(windowHandle));
#else
		BLIMP_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}

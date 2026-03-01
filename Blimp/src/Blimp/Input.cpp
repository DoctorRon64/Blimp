#include "pch.h"
#include "Blimp/Input.h"

#include "Platform/GLFW/GLFWInput.h"

namespace Blimp {
#if defined(BLIMP_PLATFORM_WINDOWS) || defined(BLIMP_PLATFORM_LINUX)
    Input* Input::s_Instance = new GLFWInput();
#else
    Input* Input::s_Instance = nullptr;
#endif
}

#include "pch.h"
#include "Blimp/Input.h"

#if defined(BLIMP_PLATFORM_WINDOWS)
#include "Platform/Windows/WindowsInput.h"
#elif defined(BLIMP_PLATFORM_LINUX)
#include "Platform/Linux/LinuxInput.h"
#endif

namespace Blimp {
#if defined(BLIMP_PLATFORM_WINDOWS)
    Input* Input::s_Instance = new WindowsInput();
#elif defined(BLIMP_PLATFORM_LINUX)
    Input* Input::s_Instance = new LinuxInput();
#else
    Input* Input::s_Instance = nullptr;
#endif
}

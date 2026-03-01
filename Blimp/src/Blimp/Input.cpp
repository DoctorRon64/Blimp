#include "pch.h"
#include "Blimp/Input.h"

#if defined(BLIMP_PLATFORM_WINDOWS)
#include "Platform/Windows/WindowsInput.h"
#elif defined(BLIMP_PLATFORM_LINUX)
#include "Platform/Linux/LinuxInput.h"
#endif

namespace Blimp {
    namespace {
        std::unique_ptr<Input> CreateInputImplementation() {
#if defined(BLIMP_PLATFORM_WINDOWS)
            return std::make_unique<WindowsInput>();
#elif defined(BLIMP_PLATFORM_LINUX)
            return std::make_unique<LinuxInput>();
#else
            return nullptr;
#endif
        }
    } // namespace

    Input& Input::Get() {
        static std::unique_ptr<Input> instance = CreateInputImplementation();
        BLIMP_CORE_ASSERT(instance, "Input system has no active platform implementation");
        return *instance;
    }
}

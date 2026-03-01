#pragma once

#include "Blimp/Core.h"
#include <utility>

namespace Blimp {
    class BLIMP_API Input {
    public:
        static bool IsKeyPressed(int keycode) {
            BLIMP_CORE_ASSERT(s_Instance, "Input system has no active platform implementation");
            return s_Instance->IsKeyPressedImplementation(keycode);
        }
        static bool IsMouseButtonPressed(int button) {
            BLIMP_CORE_ASSERT(s_Instance, "Input system has no active platform implementation");
            return s_Instance->IsMouseButtonPressedImplementation(button);
        }
        static std::pair<float, float> GetMousePos() {
            BLIMP_CORE_ASSERT(s_Instance, "Input system has no active platform implementation");
            return s_Instance->GetMousePosImplementation();
        }
        static float GetMouseX() {
            BLIMP_CORE_ASSERT(s_Instance, "Input system has no active platform implementation");
            return s_Instance->GetMouseXImplementation();
        }
        static float GetMouseY() {
            BLIMP_CORE_ASSERT(s_Instance, "Input system has no active platform implementation");
            return s_Instance->GetMouseYImplementation();
        }

    protected:
        virtual ~Input() = default;
        virtual bool IsKeyPressedImplementation(int keyCode) const = 0;
        virtual bool IsMouseButtonPressedImplementation(int button) const = 0;
        virtual std::pair<float, float> GetMousePosImplementation() const = 0;
        virtual float GetMouseXImplementation() const = 0;
        virtual float GetMouseYImplementation() const = 0;

    private:
        static Input* s_Instance;
    };
} // namespace Blimp

#pragma once

#include "Blimp/Core.h"
#include <utility>

namespace Blimp {
    class BLIMP_API Input {
    public:
        virtual ~Input() = default;

        static bool IsKeyPressed(int keycode) {
            return Get().IsKeyPressedImplementation(keycode);
        }
        static bool IsMouseButtonPressed(int button) {
            return Get().IsMouseButtonPressedImplementation(button);
        }
        static std::pair<float, float> GetMousePos() {
            return Get().GetMousePosImplementation();
        }
        static float GetMouseX() {
            return Get().GetMouseXImplementation();
        }
        static float GetMouseY() {
            return Get().GetMouseYImplementation();
        }

    protected:
        virtual bool IsKeyPressedImplementation(int keyCode) const = 0;
        virtual bool IsMouseButtonPressedImplementation(int button) const = 0;
        virtual std::pair<float, float> GetMousePosImplementation() const = 0;
        virtual float GetMouseXImplementation() const = 0;
        virtual float GetMouseYImplementation() const = 0;

    private:
        static Input& Get();
    };
} // namespace Blimp

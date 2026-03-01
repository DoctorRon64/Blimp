#pragma once

#include "Blimp/Input.h"

namespace Blimp {
    class LinuxInput : public Input {
    protected:
        bool IsKeyPressedImplementation(int keyCode) const override;
        bool IsMouseButtonPressedImplementation(int button) const override;
        std::pair<float, float> GetMousePosImplementation() const override;
        float GetMouseXImplementation() const override;
        float GetMouseYImplementation() const override;
    };
}

#pragma once

#include "Event.h"

namespace Blimp {
    class MouseMovedEvent final : public EventBase<MouseMovedEvent, EventType::MouseMoved, CategoryMask(EventCategory::Input, EventCategory::Mouse)> {
    public:
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << GetStaticName() << ": " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        static constexpr const char* GetStaticName() { return "MouseMoved"; }

    private:
        float m_MouseX = 0.0f;
        float m_MouseY = 0.0f;
    };

    class MouseScrolledEvent final : public EventBase<MouseScrolledEvent, EventType::MouseScrolled, CategoryMask(EventCategory::Input, EventCategory::Mouse)> {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << GetStaticName() << ": " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

        static constexpr const char* GetStaticName() { return "MouseScrolled"; }

    private:
        float m_XOffset = 0.0f;
        float m_YOffset = 0.0f;
    };

    class MouseButtonEvent : public Event {
    public:
        int GetMouseButton() const { return m_Button; }

        uint32_t GetCategoryFlags() const override {
            return CategoryMask(EventCategory::Input, EventCategory::Mouse, EventCategory::MouseButton);
        }

    protected:
        explicit MouseButtonEvent(int button)
            : m_Button(button) {}

        int m_Button = 0;
    };

    class MouseButtonPressedEvent final : public MouseButtonEvent {
    public:
        explicit MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}

        static constexpr EventType GetStaticType() { return EventType::MouseButtonPressed; }
        EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "MouseButtonPressed"; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << GetName() << ": " << m_Button;
            return ss.str();
        }
    };

    class MouseButtonReleasedEvent final : public MouseButtonEvent {
    public:
        explicit MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

        static constexpr EventType GetStaticType() { return EventType::MouseButtonReleased; }
        EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "MouseButtonReleased"; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << GetName() << ": " << m_Button;
            return ss.str();
        }
    };
}

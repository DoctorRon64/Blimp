#pragma once

#include "Event.h"

namespace Blimp {
    class KeyEvent : public Event {
    public:
        int GetKeyCode() const { return m_KeyCode; }

        uint32_t GetCategoryFlags() const override {
            return CategoryMask(EventCategory::Input, EventCategory::Keyboard);
        }

    protected:
        explicit KeyEvent(int keyCode)
            : m_KeyCode(keyCode) {}

        int m_KeyCode = 0;
    };

    class KeyPressedEvent final : public KeyEvent {
    public:
        KeyPressedEvent(int keyCode, int repeatCount)
            : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

        static constexpr EventType GetStaticType() { return EventType::KeyPressed; }
        EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "KeyPressed"; }

        int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << GetName() << ": " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

    private:
        int m_RepeatCount = 0;
    };

    class KeyReleasedEvent final : public KeyEvent {
    public:
        explicit KeyReleasedEvent(int keyCode)
            : KeyEvent(keyCode) {}

        static constexpr EventType GetStaticType() { return EventType::KeyReleased; }
        EventType GetEventType() const override { return GetStaticType(); }
        const char* GetName() const override { return "KeyReleased"; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << GetName() << ": " << m_KeyCode;
            return ss.str();
        }
    };
}

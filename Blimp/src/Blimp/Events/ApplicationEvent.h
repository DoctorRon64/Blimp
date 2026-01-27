#pragma once

#include "Event.h"


namespace Blimp {
    class WindowResizeEvent final : public EventBase<WindowResizeEvent, EventType::WindowResize, CategoryMask(EventCategory::Application)> {
    public:
        WindowResizeEvent(uint32_t width, uint32_t height)
            : m_Width(width), m_Height(height) {}

        uint32_t GetWidth() const { return m_Width; }
        uint32_t GetHeight() const { return m_Height; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << GetStaticName() << ": " << m_Width << ", " << m_Height;
            return ss.str();
        }

        static constexpr const char* GetStaticName() { return "WindowResize"; }

    private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
    };

    class WindowCloseEvent final : public EventBase<WindowCloseEvent, EventType::WindowClose, CategoryMask(EventCategory::Application)> {
    public:
        WindowCloseEvent() = default;
        static constexpr const char* GetStaticName() { return "WindowClose"; }
    };

    class WindowFocusEvent final : public EventBase<WindowFocusEvent, EventType::WindowFocus, CategoryMask(EventCategory::Application)> {
    public:
        WindowFocusEvent() = default;
        static constexpr const char* GetStaticName() { return "WindowFocus"; }
    };

    class WindowLostFocusEvent final : public EventBase<WindowLostFocusEvent, EventType::WindowLostFocus, CategoryMask(EventCategory::Application)> {
    public:
        WindowLostFocusEvent() = default;
        static constexpr const char* GetStaticName() { return "WindowLostFocus"; }
    };

    class WindowMovedEvent final : public EventBase<WindowMovedEvent, EventType::WindowMoved, CategoryMask(EventCategory::Application)> {
    public:
        WindowMovedEvent(int x, int y)
            : m_X(x), m_Y(y) {}

        int GetX() const { return m_X; }
        int GetY() const { return m_Y; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << GetStaticName() << ": " << m_X << ", " << m_Y;
            return ss.str();
        }

        static constexpr const char* GetStaticName() { return "WindowMoved"; }

    private:
        int m_X = 0;
        int m_Y = 0;
    };

    class AppTickEvent final : public EventBase<AppTickEvent, EventType::AppTick, CategoryMask(EventCategory::Application)> {
    public:
        AppTickEvent() = default;
        static constexpr const char* GetStaticName() { return "AppTick"; }
    };

    class AppUpdateEvent final : public EventBase<AppUpdateEvent, EventType::AppUpdate, CategoryMask(EventCategory::Application)> {
    public:
        AppUpdateEvent() = default;
        static constexpr const char* GetStaticName() { return "AppUpdate"; }
    };

    class AppRenderEvent final : public EventBase<AppRenderEvent, EventType::AppRender, CategoryMask(EventCategory::Application)> {
    public:
        AppRenderEvent() = default;
        static constexpr const char* GetStaticName() { return "AppRender"; }
    };
}
#pragma once

#include "Blimp/Core.h"



namespace Blimp {

    enum class EventType : uint8_t {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum class EventCategory : uint32_t {
        None = 0,
        Application = BIT(0),
        Input = BIT(1),
        Keyboard = BIT(2),
        Mouse = BIT(3),
        MouseButton = BIT(4)
    };

    enum class EventPhase : uint8_t {
        Capture = 0,
        Bubble
    };

    constexpr uint32_t ToMask(EventCategory category) {
        return static_cast<uint32_t>(category);
    }

    template<typename... Categories>
    constexpr uint32_t CategoryMask(Categories... categories) {
        return (ToMask(categories) | ... | 0u);
    }

    class Event {
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual uint32_t GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category) const {
            return (GetCategoryFlags() & ToMask(category)) != 0;
        }

        bool IsHandled() const { return m_Handled; }
        void SetHandled(bool handled) { m_Handled = handled; }

        void StopPropagation() { m_PropagationStopped = true; }
        bool IsPropagationStopped() const { return m_PropagationStopped; }

        EventPhase GetPhase() const { return m_Phase; }
        void SetPhase(EventPhase phase) { m_Phase = phase; }

    private:
        bool m_Handled = false;
        bool m_PropagationStopped = false;
        EventPhase m_Phase = EventPhase::Bubble;
    };

    template<typename Derived, EventType Type, uint32_t CategoryFlags>
    class EventBase : public Event {
    public:
        static constexpr EventType GetStaticType() { return Type; }
        EventType GetEventType() const override { return Type; }
        const char* GetName() const override { return Derived::GetStaticName(); }
        uint32_t GetCategoryFlags() const override { return CategoryFlags; }
    };

    class EventDispatcher {
    public:
        explicit EventDispatcher(Event& event) : m_Event(event) {}

        template<typename T, typename F>
        bool Dispatch(F&& func) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.SetHandled(std::forward<F>(func)(static_cast<T&>(m_Event)));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.ToString();
    }

}

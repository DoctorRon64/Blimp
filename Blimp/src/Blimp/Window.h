#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Blimp {
	struct WindowProperties {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& _title = "Blimp Engine",
			unsigned int _width = 1200, unsigned int _height = 700)
			: Title(_title), Width(_width), Height(_height) {}
	};

	class BLIMP_API Window {
	public:
		using EventCallbackWin = std::function<void(Event&)>;
		virtual ~Window() {};

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackWin& callback) = 0;
		virtual void SetVSync(bool _enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
};

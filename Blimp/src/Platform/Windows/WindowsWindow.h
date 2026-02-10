#pragma once
#include "Blimp/Window.h"
#include <GLFW/glfw3.h>

namespace Blimp {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return Data_.Width; }
		inline unsigned int GetHeight() const override { return Data_.Height; }

		inline void SetEventCallback(const EventCallbackWin& callback) override { Data_.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const;
		
	private:
		virtual void Init(const WindowProperties& properties);
		virtual void Terminate();

	private:
		GLFWwindow* m_Window = nullptr;

		struct WindowData {
			std::string Title;
			unsigned int Width = 0;
			unsigned int Height = 0;
			bool VSync = false;

			EventCallbackWin EventCallback;
		};

		WindowData Data_;
	};
}

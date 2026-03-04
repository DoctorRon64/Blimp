#pragma once

#include "Blimp/Window.h"
#include "Blimp/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>
#include <memory>

namespace Blimp {
	class GLFWWindow : public Window {
	public:
		GLFWWindow(const WindowProperties& properties);
		virtual ~GLFWWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackWin& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override;

	private:
		void Init(const WindowProperties& properties);
		void Terminate();

	private:
		GLFWwindow* m_Window = nullptr;
		std::unique_ptr<GraphicsContext> m_Context;

		struct WindowData {
			std::string Title;
			unsigned int Width = 0;
			unsigned int Height = 0;

			EventCallbackWin EventCallback;
		};

		WindowData m_Data;
	};
}

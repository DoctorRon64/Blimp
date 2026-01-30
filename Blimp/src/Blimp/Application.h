#pragma once

#include "Blimp/Core.h"
#include "Blimp/Events/ApplicationEvent.h"
#include "Blimp/Window.h"
#include "LayerStack.h"

namespace Blimp {
	class BLIMP_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);

		LayerStack m_LayerStack;
	};

	// to be defined in client
	Application* CreateApplication();
}

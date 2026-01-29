#pragma once

#include "Blimp/Core.h"
#include "Blimp/Events/ApplicationEvent.h"
#include "Blimp/Window.h"

namespace Blimp {
	class BLIMP_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);
	};

	// to be defined in client
	Application* CreateApplication();
}

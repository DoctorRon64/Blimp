#pragma once

#include "Blimp/Core.h"
#include "Blimp/Events/ApplicationEvent.h"
#include "Blimp/Window.h"
#include "LayerStack.h"

#include "ImGui/ImGuiLayer.h"

namespace Blimp {
	class BLIMP_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PushImGuiLayer(Layer* layer);
		void PushImGuiOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	
	private:
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		//TODO probably move this in the future
		unsigned int m_VertexArray;
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// to be defined in client
	Application* CreateApplication();
}

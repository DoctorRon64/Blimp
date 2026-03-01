#include "pch.h"
#include "Application.h"

#include "Layer.h"
#include <GLFW/glfw3.h>
#include "glad/glad.h"

#include "Input.h"

namespace Blimp {

	#define BIND_EVENT_WIN(y) std::bind(&Application::y, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		BLIMP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_WIN(OnEvent));
	}

	Application::~Application() {

	}

	void Application::Run() {
		while(m_Running) {
			glClearColor(0.3255, 0.7373, 0.6353, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for(Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			
			auto[x,y] = Input::GetMousePos();
			//BLIMP_CORE_TRACE("{0}, {1}",x, y);

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_WIN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
	}

    void Application::PushLayer(Layer *layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

    void Application::PushOverlay(Layer *layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}

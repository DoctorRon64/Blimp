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

		m_ImGuiLayer = std::make_unique<ImGuiLayer>();
		m_ImGuiLayer->OnAttach();
	}

	Application::~Application() {
		if (m_ImGuiLayer) {
			m_ImGuiLayer->OnDetach();
		}
	}

	void Application::Run() {
		while(m_Running) {
			glClearColor(0.3255, 0.7373, 0.6353, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for(Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			
			m_ImGuiLayer->Begin();
			m_ImGuiLayer->OnImGuiRender();
			for(Layer* layer : m_ImGuiLayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_WIN(OnWindowClose));

		m_ImGuiLayer->OnEvent(e);
		if (e.Handled) {
			return;
		}

		for (auto it = m_ImGuiLayerStack.end(); it != m_ImGuiLayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
		if (e.Handled) {
			return;
		}

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

    void Application::PushImGuiLayer(Layer* layer) {
		m_ImGuiLayerStack.PushLayer(layer);
		layer->OnAttach();
    }

    void Application::PushImGuiOverlay(Layer* layer) {
		m_ImGuiLayerStack.PushOverlay(layer);
		layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}

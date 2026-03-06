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

		//TODO Temperary graphics code
		//==============================================================================
		
		//Bind and reserve bufferdata VertexBuffer & IndexBuffer (Basically the complete triangle)
		glGenVertexArrays(1, &m_VertexArray);
		//Switch to this buffer
		glBindVertexArray(m_VertexArray);

		//Generate buffer for vertexBuffer in VRAM
		glGenBuffers(1, &m_VertexBuffer);
		//Switch to this buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		//The position of the vertices
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		//Upload DATA to the GPU
		//GL_STATIC_DRAW is just static we wont update this and just draw it once
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Enables vertex attribates for each vertex
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	
		//For optimalization to avoid overflow of vertices
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		//Order of the vertices
		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	Application::~Application() {
		if (m_ImGuiLayer) {
			m_ImGuiLayer->OnDetach();
		}
	}

	void Application::Run() {
		while(m_Running) {
			//TODO move this somewhere better
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

			//Render Here
			glClear(GL_COLOR_BUFFER_BIT);

			//The drawing of the buffers each frame
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			m_ImGuiLayer->Begin(); // calls ImGui::NewFrame()
			m_ImGuiLayer->OnImGuiRender(); // optional engine UI
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();   // calls ImGui::Render()
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

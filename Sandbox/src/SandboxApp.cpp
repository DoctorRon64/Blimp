#include <Blimp.h>

#include "Blimp/Events/KeyEvent.h"

class ExampleLayer : public Blimp::Layer {
	public:
	ExampleLayer() : Layer("Por_Ejemplo") {}

	void OnUpdate() override {
		//BLIMP_INFO("ExampleLayer::Update");

		if (Blimp::Input::IsKeyPressed(BLIMP_KEY_TAB)) {
			BLIMP_TRACE("TAB PRESSED");
		}
	}

	void OnEvent(Blimp::Event& event) override {
		//BLIMP_TRACE("{0}", event);
		Blimp::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Blimp::KeyPressedEvent>(BLIMP_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Blimp::KeyPressedEvent& e) {
		if (e.GetKeyCode() == BLIMP_KEY_TAB) {
			BLIMP_WARN("TAB PRESSED");
		}
		BLIMP_TRACE("{0}", (char)e.GetKeyCode());
		return false;
	}
};


class Sandbox : public Blimp::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Blimp::ImGuiLayer());
	}

	~Sandbox() = default;
};

Blimp::Application* Blimp::CreateApplication() {
	return new Sandbox(); // the actual app
}

#include <Blimp.h>

class ExampleLayer : public Blimp::Layer {
	public:
	ExampleLayer() : Layer("Por_Ejemplo") {}

	void OnUpdate() override {
		BLIMP_INFO("ExampleLayer::Update");
	}

	void OnEvent(Blimp::Event& event) override {
		BLIMP_TRACE("{0}", event);
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

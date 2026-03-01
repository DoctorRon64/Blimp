#include <Blimp.h>

#include "Blimp/Events/KeyEvent.h"

// #include <glm/vec3.hpp>
// #include <glm/vec4.hpp>
// #include <glm/mat4x4.hpp>
// #include <glm/gtc/matrix_transform.hpp>

// glm::mat4 camera(float Translate, glm::vec2 const & rotate) {
// 	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
// 	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
// 	view = glm::rotate(View, Rotate.y, glm::vec3(-1.0f,0.0,0.0f));
// 	view = glm::rotate(view, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
// 	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
// 	return Projection * view * Model;
// }

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

		if (event.GetEventType() == Blimp::EventType::KeyPressed) {
			auto& e = static_cast<Blimp::KeyPressedEvent&>(event);

			if (e.GetKeyCode() == BLIMP_KEY_TAB) {
				BLIMP_WARN("TAB PRESSED");
			}
			BLIMP_TRACE("{0}", (char)e.GetKeyCode());
		}
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

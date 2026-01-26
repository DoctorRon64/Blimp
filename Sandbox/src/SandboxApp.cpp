#include <Blimp.h>

class Sandbox : public Blimp::Application {
public:
	Sandbox();
	~Sandbox();
};

Blimp::Application* Blimp::CreateApplication() {
	return new Sandbox(); //the actual app
}

Sandbox::Sandbox() {}

Sandbox::~Sandbox() {}

#include "Blimp/EntryPoint.h"
#include "pch.h"
#include "Application.h"

namespace Blimp {
	Application::Application() {}
	Application::~Application() {}
	void Application::Run() {
		WindowResizeEvent e(1280, 900);
		BLIMP_WARN("{}", e);

		while(true);
	}
}
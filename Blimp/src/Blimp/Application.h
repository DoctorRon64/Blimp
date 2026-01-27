#pragma once

#include "Core.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Blimp {
	class BLIMP_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//to be Defined in client
	Application* CreateApplication();
}

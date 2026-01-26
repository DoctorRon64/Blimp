#pragma once

#include "Core.h"

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

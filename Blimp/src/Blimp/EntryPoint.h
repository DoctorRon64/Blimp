#pragma once

#if defined(BLIMP_PLATFORM_WINDOWS) || defined(BLIMP_PLATFORM_LINUX)

namespace Blimp {
	Application* CreateApplication();
}

int main(int argc, char** argv) {
	printf("EntryPoint \n");

	Blimp::Log::Init();
	BLIMP_TRACE("Initialized Blimp::Log");

	auto app = Blimp::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif
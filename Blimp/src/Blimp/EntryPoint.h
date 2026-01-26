#pragma once

#if defined(BLIMP_PLATFORM_WINDOWS) || defined(BLIMP_PLATFORM_LINUX)

namespace Blimp {
	Application* CreateApplication();
}

int main(int argc, char** argv) {
	printf("Blimp Engine initialized entry point!");

	Blimp::Log::Init();
	//BLIMP_CORE_WARN("Init Log");

	int variab = 5;
	//BLIMP_INFO("Hello! Var={0}", variab);

	auto app = Blimp::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif
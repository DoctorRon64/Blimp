#pragma once

#ifdef BLIMP_PLATFORM_WINDOWS

extern Blimp::Application* Blimp::CreateApplication();

int main(int argc, char** argv) {
	printf("Blimp Engine initialized entry point!");

	auto app = Blimp::CreateApplication();
	app->Run();
	delete app;
	return 0;
};

#endif
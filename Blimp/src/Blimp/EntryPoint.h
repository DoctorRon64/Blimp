#pragma once

#include "Blimp/Test.h"

#if defined(BLIMP_PLATFORM_WINDOWS) || defined(BLIMP_PLATFORM_LINUX)

namespace Blimp {
	Application* CreateApplication();
}

int main(int argc, char** argv) {
	printf("EntryPoint \n");

	Blimp::Log::Init();
	BLIMP_TRACE("Initialized Blimp::Log");

#ifdef BLIMP_RUN_TEST
	Blimp::Test test;
	test.Init();
	test.Run();
	return 0;
#else
	auto app = Blimp::CreateApplication();
	app->Run();
	delete app;
	return 0;
#endif
}

#endif

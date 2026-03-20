#include "pch.h"

#include "Blimp/Log.h"
#include "Blimp/OpenGLApplication.h"

int main(int argc, char** argv) {
	Blimp::Log::Init();
	BLIMP_TRACE("Initialized Blimp::Log");

	Blimp::OpenGLApplication app;
	app.Run();
	return 0;
}
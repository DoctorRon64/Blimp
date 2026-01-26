#pragma once

#ifdef BLIMP_PLATFORM_WINDOWS
#ifdef BLIMP_BUILD_DLL
#define BLIMP_API _declspec(dllexport)
#else
#define	BLIMP_API _declspec(dllimport)
#endif
#else
#error Blimp only supports Windows!
#endif
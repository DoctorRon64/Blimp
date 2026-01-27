#pragma once

#if defined(BLIMP_PLATFORM_WINDOWS)
#if defined(BLIMP_STATIC)
#define BLIMP_API
#elif defined(BLIMP_BUILD_DLL)
#define BLIMP_API __declspec(dllexport)
#else
#define	BLIMP_API __declspec(dllimport)
#endif
#elif defined(BLIMP_PLATFORM_LINUX)
#ifdef BLIMP_BUILD_DLL
#define BLIMP_API __attribute__((visibility("default")))
#else
#define BLIMP_API
#endif
#else
#error Blimp only supports Windows and Linux!
#endif

#define BIT(x) (1u << (x))
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

#ifdef BLIMP_ENABLE_ASSERTS
#if defined(_MSC_VER)
#define BLIMP_DEBUGBREAK() __debugbreak()
#else
#define BLIMP_DEBUGBREAK() __builtin_trap()
#endif

#define BLIMP_CORE_ASSERT(X, ...) { if(!(X)) { BLIMP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); BLIMP_DEBUGBREAK(); } }
#define BLIMP_ASSERT(X, ...) { if(!(X)) { BLIMP_ERROR("Assertion Failed: {0}", __VA_ARGS__); BLIMP_DEBUGBREAK(); } }
#else
#define BLIMP_ASSERT(x, ...)
#define BLIMP_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1u << (x))

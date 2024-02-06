#pragma once
#ifdef GE_PLATFORM_WINDOWS
#ifdef GE_BUILD_DLL
#define WIN_API __declspec(dllexport)
#else
#define WIN_API __declspec(dllimport)
#endif
#else
#error it should be windows
#endif

#ifdef GE_ENABLE_ASSERTS
#define GE_ASSERT(x, ...) { if(!(x)) { GE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define GE_CORE_ASSERT(x, ...) { if(!(x)) { GE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define GE_ASSERT(x, ...)
#define GE_CORE_ASSERT(x, ...)
#endif
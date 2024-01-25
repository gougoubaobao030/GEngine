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
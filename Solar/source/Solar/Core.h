#pragma once

#include <filesystem>

#ifdef SL_PLATFROM_WINDOWS
    #ifdef SL_BUILD_DLL
        #define SOLAR_API __declspec(dllexport)
    #else
        #define SOLAR_API __declspec(dllimport)
    #endif
#else
#error Solar only supports Windows!
#endif

#define SL_STRINGIFY_MACRO(x) #x

#ifdef SL_ENABLE_ASSERTS

#define SL_INTERNAL_ASSERT_IMPL(check, msg, ...) { if(!(check)) { SL_CORE_ERROR(msg, __VA_ARGS__); __debugbreak(); } }
#define SL_CORE_ASSERT(check) SL_INTERNAL_ASSERT_IMPL(check, "Assertion '{0}' failed at {1} Line:{2}", SL_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
#else
#define SL_ASSERT(...)
#define SL_CORE_ASSERT(...)
#endif

#define BIT(x) (1 << x)
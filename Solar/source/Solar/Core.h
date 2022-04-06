#pragma once

#ifdef SL_PLATFROM_WINDOWS
    #ifdef SL_BUILD_DLL
        #define SOLAR_API __declspec(dllexport)
    #else
        #define SOLAR_API __declspec(dllimport)
    #endif
#else
#error Solar only supports Windows!
#endif

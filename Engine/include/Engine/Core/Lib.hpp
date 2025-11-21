#pragma once

#if defined(_WIN32) || defined(_WIN64)
    #ifdef CC_ENGINE_EXPORTS
    /*Enabled as "export" while compiling the dll project*/
    #define DLLEXPORT __declspec(dllexport)
    #else
    /*Enabled as "import" in the Client side for using already created dll file*/
    #define DLLEXPORT __declspec(dllimport)
    #endif
#else
    #ifdef CC_ENGINE_EXPORTS
    #define DLLEXPORT __attribute__((visibility("default")))
    #else
    #define DLLEXPORT
    #endif
#endif

#pragma once
#include <stdint.h>
#include <string>

struct HardwareInfo
{
    uint32_t CPUCount = 0;
    uint32_t GPUCount = 0;
    uint32_t RAMSize = 0;  // in MB
    uint32_t VRAMSize = 0; // in MB
    uint32_t VRAMFree = 0; // in MB
};

struct Platform
{
    enum class Type
    {
        kWindows,
        kLinux,
        kMacOS,
        kAndroid,
        kIOS,
        kWebAssembly,
        kUnknown
    };

    constexpr const char *GetPlatformName() noexcept
    {
        return GetPlatformName(GetPlatform());
    }
    constexpr const char *GetPlatformName(Type platform) noexcept
    {
        switch (platform)
        {
        case Type::kWindows:
            return "Windows";
        case Type::kLinux:
            return "Linux";
        case Type::kMacOS:
            return "MacOS";
        case Type::kAndroid:
            return "Android";
        case Type::kIOS:
            return "iOS";
        case Type::kWebAssembly:
            return "WebAssembly";
        default:
            return "Unknown";
        }
    }

    constexpr Type GetPlatform() noexcept
    {
#if defined(_WIN32) || defined(_WIN64)
        return Type::kWindows;
#elif defined(__linux__)
        return Type::kLinux;
#elif defined(__APPLE__) || defined(__MACH__)
        return Type::kMacOS;
#elif defined(__ANDROID__)
        return Type::kAndroid;
#elif defined(__APPLE__)
        return Type::kIOS;
#elif defined(__EMSCRIPTEN__)
        return Type::kWebAssembly;
#else
        return Type::kUnknown;
#endif
    }
    constexpr bool IsWindows() noexcept { return GetPlatform() == Type::kWindows; }
    constexpr bool IsLinux() noexcept { return GetPlatform() == Type::kLinux; }
    constexpr bool IsMacOS() noexcept { return GetPlatform() == Type::kMacOS; }
    constexpr bool IsAndroid() noexcept { return GetPlatform() == Type::kAndroid; }
    constexpr bool IsIOS() noexcept { return GetPlatform() == Type::kIOS; }
    constexpr bool IsWebAssembly() noexcept { return GetPlatform() == Type::kWebAssembly; }
    constexpr bool IsUnknown() noexcept { return GetPlatform() == Type::kUnknown; }

    constexpr bool IsMobile() noexcept { return IsAndroid() || IsIOS(); }
    constexpr bool IsDesktop() noexcept { return !IsMobile(); }
};

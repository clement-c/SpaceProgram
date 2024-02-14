#pragma once
#include <stdint.h>

struct RenderTargetSurface
{
    uint32_t width, height;
    // pixelFormat
    size_t windowId = 0;
};

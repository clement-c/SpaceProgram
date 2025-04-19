#pragma once

#include <cstdint>

struct FrameBuffer
{
    uint32_t width;
    uint32_t height;
    // uint32_t colorAttachment; // ID for the color attachment (e.g., texture)
    // uint32_t depthAttachment; // ID for the depth attachment (optional)

    FrameBuffer(uint32_t width, uint32_t height);
    ~FrameBuffer();

private:
    uint32_t frameBufferID; // OpenGL or other API-specific framebuffer ID

    void Create();
    void Destroy();
};

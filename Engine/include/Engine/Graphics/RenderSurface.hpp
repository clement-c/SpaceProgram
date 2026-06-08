#pragma once
#include <stdint.h>

/**
 * @brief A RenderSurface is passed to the Renderer in order to
 *
 */
struct RenderSurface
{
    uint32_t Width = 1280, Height = 720;
    float UIScaleMultiplier = 1.0f;

    uint32_t ClearColor[4] = {15, 50, 10, 255}; // RGBA

    /// @brief Returns the aspect ratio of the render surface.
    /// @return The aspect ratio as a float.
    float GetAspectRatio() const
    {
        return Height > 0 ? static_cast<float>(Width) / static_cast<float>(Height) : 0.0f;
    }

    /**
     * @brief Updates the dimensions of the render surface.
     * @param width The new width of the render surface.
     * @param height The new height of the render surface.
     * @return A reference to the updated RenderSurface object.
     */
    RenderSurface &UpdateDimensions(uint32_t width, uint32_t height)
    {
        Width = width;
        Height = height;
        return *this;
    }

    /**
     * @brief Updates the UIScaleMultiplier of the render surface.
     * @param scale The new UIScaleMultiplier.
     * @return A reference to the updated RenderSurface object.
     */
    RenderSurface &UpdateUIScale(float scale)
    {
        UIScaleMultiplier = scale;
        return *this;
    }

    RenderSurface &SetClearColor(float r, float g, float b, float a)
    {
        ClearColor[0] = r;
        ClearColor[1] = g;
        ClearColor[2] = b;
        ClearColor[3] = a;
        return *this;
    }
};

#pragma once
#include <stdint.h>


/**
 * @brief A RenderSurface is passed to the Renderer in order to
 *
 */
struct RenderSurface
{
    uint32_t Width = 1280, Height = 720;
    float Ratio = 1.0f;
    float UIScaleMultiplier = 1.0f;

    /// @brief Returns the aspect ratio of the render surface.
    /// @return The aspect ratio as a float.
    float GetAspectRatio() const
    {
        return Width > 0 ? static_cast<float>(Width) / static_cast<float>(Height) : 0.0f;
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
        Ratio = static_cast<float>(Width) / static_cast<float>(Height);
        return *this;
    }
};

#pragma once

struct Texture
{
    enum class PixelFormat : int
    {
        kRGB = 0,
        kRGBA = 1,
        kBGR = 2,
        kBGRA = 3,
        kLuminance = 4,
        kAlpha = 5
    };
    enum class Type : int
    {
        k2D = 0,
        k3D = 1,
        kCubeMap = 2,
        kBuffer = 3,
        kRectangle = 4
    };

    Texture(PixelFormat pixelFormat = PixelFormat::kRGBA, Type type = Type::k2D, int width = 0, int height = 0, int depth = 0)
        : m_pixelFormat(pixelFormat), m_type(type), m_width(width), m_height(height), m_depth(depth) {}
    ~Texture() = default;

    PixelFormat GetPixelFormat() const { return m_pixelFormat; }
    Type GetType() const { return m_type; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    int GetDepth() const { return m_depth; }

private:
    PixelFormat m_pixelFormat;
    Type m_type;
    int m_width, m_height, m_depth;
};

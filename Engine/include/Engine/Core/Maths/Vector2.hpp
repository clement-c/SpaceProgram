#pragma once

#include "Constants.hpp"
#include <array>

struct Vector2
{
    static constexpr Vector2 X()
    {
        return Vector2{1.0, 0.0};
    }
    static constexpr Vector2 Y()
    {
        return Vector2{0.0, 1.0};
    }

    constexpr Vector2() = default;
    constexpr Vector2(Scalar xx, Scalar yy) : x{xx}, y{yy} {}

    inline Scalar &operator[](uint32_t i)
    {
        return data[i];
    }

    Vector2 &operator+=(Vector2 const &other) noexcept
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2 &operator-=(Vector2 const &other) noexcept
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2 &operator*=(Scalar scale) noexcept
    {
        x *= scale;
        y *= scale;
        return *this;
    }

    Vector2 &operator/=(Scalar scale)
    {
        x /= scale;
        y /= scale;
        return *this;
    }

    constexpr Vector2 Scaled(Scalar const scale) const
    {
        return Vector2{x * scale, y * scale};
    }

    inline Vector2 &Scale(Scalar const scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }

    constexpr Vector2 Negated() const
    {
        return Scaled(static_cast<Scalar>(-1.0));
    }

    inline Vector2 &Negate()
    {
        return Scale(static_cast<Scalar>(-1.0));
    }

    constexpr Scalar Dot(Vector2 const &other) const noexcept(true)
    {
        return (x * other.x + y * other.y);
    }

    constexpr Scalar MagnitudeSquared() const
    {
        return Dot(*this);
    }

    inline Scalar Magnitude() const noexcept
    {
        return std::sqrt(MagnitudeSquared());
    }

    Vector2 &Normalize()
    {
        Scalar r = (Scalar)1.0f / Magnitude();
        x *= r;
        y *= r;
        return *this;
    }

    inline Vector2 Normalized() const
    {
        return Vector2(*this).Normalize();
    }

    inline Vector2 Project(Vector2 const &onto) const
    {
        return onto.Scaled((*this).Dot(onto) / onto.MagnitudeSquared());
    }

    /**
     * @brief Returns the counterclockwise perpendicular vector
     *
     * @return Vector2
     */
    inline Vector2 Perp() const;

    union
    {
        struct
        {
            Scalar x, y;
        };
        std::array<Scalar, 3> data = {0., 0.};
    };
};

constexpr Vector2 operator+(Vector2 const &a, Vector2 const &b)
{
    return Vector2(a.x + b.x, a.y + b.y);
}

constexpr Vector2 operator-(Vector2 const &vec)
{
    return vec.Negated();
}

constexpr Vector2 operator-(Vector2 const &a, Vector2 const &b)
{
    return Vector2(a.x - b.x, a.y - b.y);
}

constexpr Vector2 operator*(Vector2 const &vec, Scalar scale)
{
    return Vector2(vec.x * scale, vec.y * scale);
}

constexpr Vector2 operator*(Scalar scale, Vector2 const &vec)
{
    return Vector2(vec.x * scale, vec.y * scale);
}

constexpr Scalar operator*(Vector2 const &vecA, Vector2 const &vecB)
{
    return vecA.Dot(vecB);
}

constexpr bool operator==(Vector2 const &vecA, Vector2 const &vecB)
{
    return vecA.x == vecB.x && vecA.y == vecB.y;
}

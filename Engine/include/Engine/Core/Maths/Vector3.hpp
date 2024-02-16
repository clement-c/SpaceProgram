#pragma once
#include "Constants.hpp"
#include <array>

struct Vector4;

struct Vector3 // alignas(4 * sizeof(float)) Vector3
{
    static constexpr Vector3 X()
    {
        return Vector3{1.0, 0.0, 0.0};
    }
    static constexpr Vector3 Y()
    {
        return Vector3{0.0, 1.0, 0.0};
    }
    static constexpr Vector3 Z()
    {
        return Vector3{0.0, 0.0, 1.0};
    }
    static constexpr Vector3 Zero()
    {
        return Vector3{kZero, kZero, kZero};
    }

    constexpr Vector3() = default;
    constexpr Vector3(Scalar xx, Scalar yy, Scalar zz) : x{xx}, y{yy}, z{zz} {}
    operator Vector4();

    inline Scalar &operator[](uint32_t i)
    {
        return data[i];
    }

    Vector3 &operator+=(Vector3 const &other) noexcept
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3 &operator-=(Vector3 const &other) noexcept
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3 &operator*=(Scalar scale) noexcept
    {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    Vector3 &operator/=(Scalar scale)
    {
        x /= scale;
        y /= scale;
        z /= scale;
        return *this;
    }

    constexpr Vector3 Scaled(Scalar const scale) const
    {
        return Vector3{x * scale, y * scale, z * scale};
    }

    inline Vector3 &Scale(Scalar const scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    constexpr Vector3 Negated() const
    {
        return Scaled(static_cast<Scalar>(-1.0));
    }

    inline Vector3 &Negate()
    {
        return Scale(static_cast<Scalar>(-1.0));
    }

    constexpr Scalar Dot(Vector3 const &other) const noexcept(true)
    {
        return (x * other.x + y * other.y + z * other.z);
    }

    constexpr Vector3 Cross(Vector3 const &other) const noexcept
    {
        return Vector3(
            y * other.z - other.y * z, z * other.x - other.z * x, x * other.y - y * other.x);
    }

    constexpr Scalar MagnitudeSquared() const
    {
        return Dot(*this);
    }

    inline Scalar Magnitude() const noexcept
    {
        return std::sqrt(MagnitudeSquared());
    }

    Vector3 &Normalize()
    {
        Scalar r = (Scalar)1.0f / Magnitude();
        x *= r;
        y *= r;
        z *= r;
        return *this;
    }

    inline Vector3 Normalized() const
    {
        return Vector3(*this).Normalize();
    }

    inline Vector3 Project(Vector3 const &onto) const
    {
        return onto.Scaled((*this).Dot(onto) / onto.MagnitudeSquared());
    }

    union
    {
        struct
        {
            Scalar x, y, z;
        };
        std::array<Scalar, 3> data = {0., 0., 0.};
    };
};

constexpr Vector3 operator+(Vector3 const &a, Vector3 const &b)
{
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

constexpr Vector3 operator-(Vector3 const &vec)
{
    return vec.Negated();
}

constexpr Vector3 operator-(Vector3 const &a, Vector3 const &b)
{
    return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

constexpr Vector3 operator*(Vector3 const &vec, Scalar scale)
{
    return Vector3(vec.x * scale, vec.y * scale, vec.z * scale);
}

constexpr Vector3 operator*(Scalar scale, Vector3 const &vec)
{
    return Vector3(vec.x * scale, vec.y * scale, vec.z * scale);
}

constexpr Scalar operator*(Vector3 const &vecA, Vector3 const &vecB)
{
    return vecA.Dot(vecB);
}

constexpr bool operator==(Vector3 const &vecA, Vector3 const &vecB)
{
    return vecA.x == vecB.x && vecA.y == vecB.y && vecA.z == vecB.z;
}

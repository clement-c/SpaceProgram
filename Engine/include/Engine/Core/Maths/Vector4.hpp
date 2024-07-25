#pragma once
#include <array>

#include "Constants.hpp"
#include "Vector3.hpp"

struct Vector4
{
    static constexpr Vector4 X()
    {
        return Vector4{kOne, kZero, kZero};
    }
    static constexpr Vector4 Y()
    {
        return Vector4{kZero, kOne, kZero};
    }
    static constexpr Vector4 Z()
    {
        return Vector4{kZero, kZero, kOne};
    }
    static constexpr Vector4 Zero()
    {
        return Vector4{kZero, kZero, kZero};
    }

    constexpr Vector4() = default;
    constexpr Vector4(Scalar xx, Scalar yy, Scalar zz, Scalar ww = 1.0) : x{xx}, y{yy}, z{zz}, w{ww} {}
    constexpr Vector4(Vector3 const &vec, Scalar w_ = static_cast<Scalar>(1.0)) : x{vec.x}, y{vec.y}, z{vec.z}, w{w_} {}

    Vector4 &operator=(Vector3 const &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = kOne;
        return *this;
    }

    inline Scalar &operator[](int32_t i)
    {
        return data[i % 4];
    }

    Vector4 &Homogenize()
    {
        auto ratio = kOne / w;
        x *= ratio;
        y *= ratio;
        z *= ratio;
        w = kOne;
        return *this;
    }

    constexpr Vector3 Cartesian() const
    {
        auto ratio = kOne / w;
        return Vector3{x * ratio, y * ratio, z * ratio};
    }

    constexpr operator Vector3() const
    {
        return Vector3{x, y, z}; // NOT CARTESIAN
    }

    union
    {
        struct
        {
            Scalar x, y, z, w;
        };
        std::array<Scalar, 4> data = {kZero, kZero, kZero, kOne};
    };
};

constexpr Vector4 &operator-(Vector4 &vec)
{
    vec.x *= kMinusOne;
    vec.y *= kMinusOne;
    vec.z *= kMinusOne;
    return vec;
}

constexpr Vector3 operator-(Vector4 const &vecA, Vector4 const &vecB)
{
    return vecA.Cartesian() - vecB.Cartesian();
}

constexpr Vector3 operator+(Vector4 const &ptA, Vector3 const &vecB)
{
    auto cartesian = ptA.Cartesian();
    return Vector4(cartesian.x + vecB.x, cartesian.x + vecB.y, cartesian.x + vecB.z);
}

constexpr Vector4 operator*(Vector4 const &vec, Scalar scale)
{
    return Vector4{vec.x * scale, vec.y * scale, vec.z * scale, vec.w};
}

constexpr Vector4 operator*(Scalar scale, Vector4 const &vec)
{
    return Vector4{vec.x * scale, vec.y * scale, vec.z * scale, vec.w};
}

constexpr Vector4 operator/(Vector4 const &vec, Scalar scale)
{
    return Vector4{vec.x / scale, vec.y / scale, vec.z / scale, vec.w};
}

constexpr Vector4 operator/(Scalar scale, Vector4 const &vec)
{
    return Vector4{vec.x / scale, vec.y / scale, vec.z / scale, vec.w};
}

constexpr bool operator==(Vector4 const &vecA, Vector4 const &vecB)
{
    return vecA.x == vecB.x && vecA.y == vecB.y && vecA.z == vecB.z && vecA.w == vecB.w;
}

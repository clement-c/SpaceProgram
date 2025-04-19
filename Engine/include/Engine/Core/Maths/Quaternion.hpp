#pragma once
#include <array>
#include <cmath>

#include "Constants.hpp"
#include "Vector3.hpp"

struct Quaternion
{

    static constexpr Quaternion I()
    {
        return Quaternion{1.0, 0.0, 0.0, 0.0};
    }

    static constexpr Quaternion J()
    {
        return Quaternion{0.0, 1.0, 0.0, 0.0};
    }

    static constexpr Quaternion K()
    {
        return Quaternion{0.0, 0.0, 1.0, 0.0};
    }

    static constexpr Quaternion Identity()
    {
        return Quaternion{0.0, 0.0, 0.0, 1.0};
    }

    static constexpr Quaternion Zero()
    {
        return Quaternion{0.0, 0.0, 0.0, 0.0};
    }

    constexpr Quaternion() = default;
    constexpr Quaternion(Scalar xx, Scalar yy, Scalar zz, Scalar ww = 1.0) : x{xx}, y{yy}, z{zz}, w{ww} {}
    constexpr Quaternion(std::array<Scalar, 4> const& arr) : x{arr[0]}, y{arr[1]}, z{arr[2]}, w{arr[3]} {}
    constexpr Quaternion(Quaternion const &other) = default;
    constexpr Quaternion(Quaternion &&other) = default;

    constexpr Quaternion& operator=(Quaternion const &other) = default;
    constexpr Quaternion& operator=(Quaternion &&other) = default;
    constexpr Quaternion& operator=(std::array<Scalar, 4> const& arr)
    {
        x = arr[0];
        y = arr[1];
        z = arr[2];
        w = arr[3];
        return *this;
    }
    constexpr Quaternion& operator=(std::array<Scalar, 4> &&arr)
    {
        x = arr[0];
        y = arr[1];
        z = arr[2];
        w = arr[3];
        return *this;
    }

    constexpr Quaternion Conjugate() const
    {
        return Quaternion{-x, -y, -z, w};
    }


    union
    {
        struct
        {
            Scalar x, y, z, w;
        };
        std::array<Scalar, 4> data = {0.0, 0.0, 0.0, 1.0};
    };
};

constexpr bool operator==(Quaternion const &vecA, Quaternion const &vecB)
{
    return vecA.x == vecB.x && vecA.y == vecB.y && vecA.z == vecB.z && vecA.w == vecB.w;
}

constexpr bool operator!=(Quaternion const &vecA, Quaternion const &vecB)
{
    return !(vecA == vecB);
}

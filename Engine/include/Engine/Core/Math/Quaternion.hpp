#pragma once
#include <array>

#include "Constants.hpp"

struct Quaternion
{

    constexpr Quaternion() = default;
    constexpr Quaternion(Scalar xx, Scalar yy, Scalar zz, Scalar ww = 1.0) : x{xx}, y{yy}, z{zz}, w{ww} {}

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
    return vecA.x != vecB.x && vecA.y != vecB.y && vecA.z != vecB.z && vecA.w != vecB.w;
}

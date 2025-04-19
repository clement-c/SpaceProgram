#pragma once
#include "Maths/Vector4.hpp"

struct Color
{
    union
    {
        Vector4 rgba;
        struct {
            Scalar r, g, b, a;
        };
    };
};

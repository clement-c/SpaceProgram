#pragma once

#include <cmath>
#include "Constants.hpp"

// Fast approximation of sine using a polynomial approximation
inline float FastSin(float x) {
    // Wrap input angle to [-π, π]
    x = fmod(x + kPi, 2 * kPi) - kPi;

    // Approximation: sin(x) ≈ x * (1 - x^2 / 6)
    return x * (1 - (x * x) / 6.0f);
}

// Fast approximation of cosine using a polynomial approximation
inline float FastCos(float x) {
    // Use the identity: cos(x) = sin(x + π/2)
    return FastSin(x + kPiHalf);
}

// Fast approximation of tangent using sine and cosine
inline float FastTan(float x) {
    float sinVal = FastSin(x);
    float cosVal = FastCos(x);

    // Avoid division by zero
    if (cosVal == 0.0f) {
        return (sinVal > 0.0f) ? INFINITY : -INFINITY;
    }

    return sinVal / cosVal;
}

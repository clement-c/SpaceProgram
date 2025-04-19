#pragma once
#include <limits>
#include <cmath>
#include <stdint.h>

#ifdef MATHS_DOUBLE_PRECISION
using Scalar = double;
#else
using Scalar = float;
#endif

constexpr Scalar kZero = static_cast<Scalar>(0.0);
constexpr Scalar kHalf = static_cast<Scalar>(0.5);
constexpr Scalar kOne = static_cast<Scalar>(1.0);
constexpr Scalar kTwo = static_cast<Scalar>(2.0);
constexpr Scalar kMinusOne = static_cast<Scalar>(-1.0);

constexpr Scalar kEpsilon = ::std::numeric_limits<Scalar>::epsilon();

constexpr Scalar kPi = static_cast<Scalar>(3.1415926535897932384626433);
constexpr Scalar kPiHalf = static_cast<Scalar>(1.57079632679489661923132165);
constexpr Scalar kPiInverse = static_cast<Scalar>(0.3183098861837906715377675);

constexpr Scalar kDegToRad = static_cast<Scalar>(0.01745329251994329576923691);
constexpr Scalar kRadToDeg = static_cast<Scalar>(57.295779513082320876798156);

constexpr Scalar kE = static_cast<Scalar>(2.7182818284590452353602875);
constexpr Scalar kGoldenRatio = static_cast<Scalar>(1.618033988749895);
constexpr Scalar kSqrt2 = static_cast<Scalar>(1.4142135623730950488016887);
constexpr Scalar kSqrt3 = static_cast<Scalar>(1.7320508075688772935274463);
constexpr Scalar kSqrt5 = static_cast<Scalar>(2.2360679774997896964091731);
constexpr Scalar kSqrtPi = static_cast<Scalar>(1.7724538509055160272981674);
constexpr Scalar kSqrt2Pi = static_cast<Scalar>(2.5066282746310005024157651);

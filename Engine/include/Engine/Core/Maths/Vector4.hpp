#pragma once
#include <array>

#include "../Lib.hpp"
#include "Constants.hpp"
#include "Vector3.hpp"

struct Vector4
/**
 * @brief Represents a 4-dimensional vector with homogeneous coordinates.
 * 
 * This class provides utility functions and operators for working with 4D vectors,
 * including Cartesian conversion, homogenization, and component access.
 */
{
    /**
     * @brief Returns a unit vector along the X-axis.
     * @return A Vector4 with components (1, 0, 0, 1).
     */
    static constexpr Vector4 X();

    /**
     * @brief Returns a unit vector along the Y-axis.
     * @return A Vector4 with components (0, 1, 0, 1).
     */
    static constexpr Vector4 Y();

    /**
     * @brief Returns a unit vector along the Z-axis.
     * @return A Vector4 with components (0, 0, 1, 1).
     */
    static constexpr Vector4 Z();

    /**
     * @brief Returns a zero vector.
     * @return A Vector4 with components (0, 0, 0, 1).
     */
    static constexpr Vector4 Zero();

    /**
     * @brief Default constructor. Initializes the vector to (0, 0, 0, 1).
     */
    DLLEXPORT constexpr Vector4() = default;

    /**
     * @brief Constructs a Vector4 with specified components.
     * @param xx The X component.
     * @param yy The Y component.
     * @param zz The Z component.
     * @param ww The W component (default is 1.0).
     */
    DLLEXPORT constexpr Vector4(Scalar xx, Scalar yy, Scalar zz, Scalar ww = 1.0);

    /**
     * @brief Constructs a Vector4 from a Vector3 and a W component.
     * @param vec The 3D vector to copy components from.
     * @param w_ The W component (default is 1.0).
     */
    DLLEXPORT constexpr Vector4(Vector3 const &vec, Scalar w_ = static_cast<Scalar>(1.0));

    /**
     * @brief Assigns the components of a Vector3 to this Vector4.
     * 
     * The W component is set to 1.0.
     * @param vec The 3D vector to assign.
     * @return A reference to this Vector4.
     */
    DLLEXPORT Vector4 &operator=(Vector3 const &vec);

    /**
     * @brief Accesses a component of the vector by index.
     * 
     * The index is wrapped modulo 4.
     * @param i The index of the component (0 for X, 1 for Y, 2 for Z, 3 for W).
     * @return A reference to the selected component.
     */
    DLLEXPORT constexpr Scalar &operator[](int32_t i)
    {
        return data[i % 4];
    }
    
    /**
     * @brief Converts the vector to its homogeneous form.
     * 
     * Divides the X, Y, and Z components by the W component, and sets W to 1.0.
     * @return A reference to this Vector4.
     */
    DLLEXPORT Vector4 &Homogenize();

    /**
     * @brief Converts the vector to a 3D Cartesian vector.
     * 
     * Divides the X, Y, and Z components by the W component.
     * @return A Vector3 representing the Cartesian coordinates.
     */
    DLLEXPORT constexpr Vector3 Cartesian() const;

    /**
     * @brief Implicitly converts this Vector4 to a Vector3.
     * 
     * The W component is ignored, and the X, Y, and Z components are copied directly.
     * @return A Vector3 with the X, Y, and Z components of this Vector4.
     */
    DLLEXPORT constexpr operator Vector3() const;

    /**
     * @brief Union for accessing vector components as individual scalars or as an array.
     */
    union
    {
        struct
        {
            Scalar x; ///< The X component.
            Scalar y; ///< The Y component.
            Scalar z; ///< The Z component.
            Scalar w; ///< The W component.
        };
        std::array<Scalar, 4> data = {kZero, kZero, kZero, kOne}; ///< Array representation of the vector.
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

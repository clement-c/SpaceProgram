#pragma once
#include "Engine/Core/Lib.hpp"
#include "Constants.hpp"
#include <array>

struct Vector4;

struct Vector3 // alignas(4 * sizeof(float)) Vector3
/**
 * @class Vector3
 * @brief A 3D vector class providing basic vector operations.
 *
 * This class represents a 3D vector and provides various utility functions
 * for vector arithmetic, normalization, projection, and other operations.
 *
 * @note The class uses a union to allow access to vector components as either
 *       individual `x`, `y`, `z` members or as an array `data`.
 */
{
    /**
     * @brief Returns the unit vector along the X-axis.
     * @return A Vector3 representing (1.0, 0.0, 0.0).
     */
    static constexpr Vector3 X() { return Vector3{1.0, 0.0, 0.0}; };

    /**
     * @brief Returns the unit vector along the Y-axis.
     * @return A Vector3 representing (0.0, 1.0, 0.0).
     */
    static constexpr Vector3 Y() { return Vector3{0.0, 1.0, 0.0}; } ;

    /**
     * @brief Returns the unit vector along the Z-axis.
     * @return A Vector3 representing (0.0, 0.0, 1.0).
     */
    static constexpr Vector3 Z() { return Vector3{0.0, 0.0, 1.0}; };

    /**
     * @brief Returns the zero vector.
     * @return A Vector3 representing (0.0, 0.0, 0.0).
     */
    static constexpr Vector3 Zero() { return Vector3{0.0, 0.0, 0.0}; };

    /**
     * @brief Default constructor.
     * Initializes the vector to (0.0, 0.0, 0.0).
     */
    constexpr Vector3() = default;

    /**
     * @brief Constructs a vector with specified components.
     * @param xx The X component.
     * @param yy The Y component.
     * @param zz The Z component.
     */
    DLLEXPORT constexpr Vector3(Scalar xx, Scalar yy, Scalar zz) : data{xx, yy, zz} {};

    /**
     * @brief Converts this Vector3 to a Vector4.
     */
    DLLEXPORT constexpr operator Vector4() const;

    /**
     * @brief Accesses the vector component by index.
     * @param i The index (0 for x, 1 for y, 2 for z).
     * @return A reference to the component.
     */
    DLLEXPORT constexpr Scalar &operator[](uint32_t i);

    /**
     * @brief Adds another vector to this vector.
     * @param other The vector to add.
     * @return A reference to this vector after addition.
     */
    DLLEXPORT Vector3 &operator+=(Vector3 const &other) noexcept;

    /**
     * @brief Subtracts another vector from this vector.
     * @param other The vector to subtract.
     * @return A reference to this vector after subtraction.
     */
    DLLEXPORT Vector3 &operator-=(Vector3 const &other) noexcept;

    /**
     * @brief Multiplies this vector by a scalar.
     * @param scale The scalar value.
     * @return A reference to this vector after scaling.
     */
    DLLEXPORT Vector3 &operator*=(Scalar scale) noexcept;

    /**
     * @brief Divides this vector by a scalar.
     * @param scale The scalar value.
     * @return A reference to this vector after division.
     */
    DLLEXPORT Vector3 &operator/=(Scalar scale);

    /**
     * @brief Returns a scaled copy of this vector.
     * @param scale The scalar value.
     * @return A new Vector3 scaled by the given value.
     */
    DLLEXPORT constexpr Vector3 Scaled(Scalar const scale) const;

    /**
     * @brief Scales this vector by a scalar.
     * @param scale The scalar value.
     * @return A reference to this vector after scaling.
     */
    DLLEXPORT inline Vector3 &Scale(Scalar const scale);

    /**
     * @brief Returns a negated copy of this vector.
     * @return A new Vector3 with all components negated.
     */
    DLLEXPORT constexpr Vector3 Negated() const;

    /**
     * @brief Negates this vector.
     * @return A reference to this vector after negation.
     */
    DLLEXPORT inline Vector3 &Negate();

    /**
     * @brief Computes the dot product with another vector.
     * @param other The other vector.
     * @return The dot product as a scalar.
     */
    DLLEXPORT constexpr Scalar Dot(Vector3 const &other) const noexcept(true);

    /**
     * @brief Computes the cross product with another vector.
     * @param other The other vector.
     * @return A new Vector3 representing the cross product.
     */
    DLLEXPORT constexpr Vector3 Cross(Vector3 const &other) const noexcept;

    /**
     * @brief Computes the squared magnitude of this vector.
     * @return The squared magnitude as a scalar.
     */
    DLLEXPORT constexpr Scalar MagnitudeSquared() const;

    /**
     * @brief Computes the magnitude (length) of this vector.
     * @return The magnitude as a scalar.
     */
    DLLEXPORT inline Scalar Magnitude() const noexcept;

    /**
     * @brief Normalizes this vector to have a magnitude of 1.
     * @return A reference to this vector after normalization.
     */
    DLLEXPORT Vector3 &Normalize();

    /**
     * @brief Returns a normalized copy of this vector.
     * @return A new Vector3 with a magnitude of 1.
     */
    DLLEXPORT inline Vector3 Normalized() const;

    /**
     * @brief Projects this vector onto another vector.
     * @param onto The vector to project onto.
     * @return A new Vector3 representing the projection.
     */
    DLLEXPORT inline Vector3 Project(Vector3 const &onto) const;

    /**
     * @union
     * @brief Provides access to vector components as individual members or as an array.
     *
     * @var x The X component of the vector.
     * @var y The Y component of the vector.
     * @var z The Z component of the vector.
     * @var data An array representation of the vector components.
     */
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

constexpr bool operator!=(Vector3 const &vecA, Vector3 const &vecB)
{
    return !(vecA == vecB);
}

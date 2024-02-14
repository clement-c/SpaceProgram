#pragma once
#include <array>
#include <cmath>

#include "Constants.hpp"
#include "Euler.hpp"
#include "Vector3.hpp"

struct Matrix33
{
    static Matrix33 Identity()
    {
        return Matrix33{{kOne, kZero, kZero,
                         kZero, kOne, kZero,
                         kZero, kZero, kOne}};
    }

    /**
     * @brief Build a rotation matrix for a rotation in radians around axis X
     *
     * @param angleRad
     * @return Matrix33
     */
    static Matrix33 RotationX(Scalar angleRad)
    {
        return {
            kOne, kZero, kZero,
            kZero, cos(angleRad), sin(angleRad),
            kZero, -sin(angleRad), cos(angleRad)};
    }

    /**
     * @brief Build a rotation matrix for a rotation in radians around axis Y
     *
     * @param angleRad
     * @return Matrix33
     */
    static Matrix33 RotationY(Scalar angleRad)
    {
        return {
            cos(angleRad), kZero, -sin(angleRad),
            kZero, kOne, kZero,
            sin(angleRad), kZero, cos(angleRad)};
    }

    /**
     * @brief Build a rotation matrix for a rotation in radians around axis Z
     *
     * @param angleRad
     * @return Matrix33
     */
    static Matrix33 RotationZ(Scalar angleRad)
    {
        return {
            cos(angleRad), sin(angleRad), kZero,
            -sin(angleRad), cos(angleRad), kZero,
            kZero, kZero, kOne};
    }

    constexpr Matrix33() = default;
    constexpr Matrix33(Matrix33 const &other) = default;
    constexpr Matrix33(std::array<Scalar, 9> const &arr) : data{arr} {}
    constexpr Matrix33(
        Scalar i00, Scalar i01, Scalar i02,
        Scalar i10, Scalar i11, Scalar i12,
        Scalar i20, Scalar i21, Scalar i22) : data{i00, i01, i02, i10, i11, i12, i20, i21, i22} {}
    constexpr Matrix33(Vector3 const &rowA, Vector3 const &rowB, Vector3 const &rowC) : row0{rowA}, row1{rowB}, row2{rowC} {}

    inline Scalar &operator()(uint32_t row, uint32_t comp)
    {
        return data[row * 3 + comp];
    }
    constexpr Scalar const &operator()(uint32_t row, uint32_t comp) const
    {
        return data[row * 3 + comp];
    }

    inline Vector3 &operator[](uint32_t i)
    {
        *reinterpret_cast<Vector3 *>(&data[3 * i]);
    }

    inline Vector3 const &operator[](uint32_t i) const
    {
        *reinterpret_cast<Vector3 const *>(&data[3 * i]);
    }

    constexpr Vector3 Column(uint32_t colId) const
    {
        return Vector3(data[colId], data[3 + colId], data[6 + colId]);
    }

    Matrix33 &Transpose()
    {
        std::swap(data[1], data[3]);
        std::swap(data[2], data[6]);
        std::swap(data[5], data[7]);
        return *this;
    }

    inline Matrix33 Transposed() const
    {
        return Matrix33{a00, a10, a20, a01, a11, a21, a02, a12, a22};
    }

    constexpr Scalar Determinant() const
    {
        return a00 * (a11 * a22 - a12 * a21) - a01 * (a10 * a22 - a12 * a20) + a02 * (a10 * a21 - a11 * a20);
    }

    constexpr Matrix33 HadamardProduct(Matrix33 const &other)
    {
        return {
            a00 * other.a00, a01 * other.a01, a02 * other.a02,
            a10 * other.a10, a11 * other.a11, a12 * other.a12,
            a20 * other.a20, a21 * other.a21, a22 * other.a22};
    }

    union
    {
        struct
        {
            Scalar a00, a01, a02,
                a10, a11, a12,
                a20, a21, a22;
        };
        struct
        {
            Vector3 row0, row1, row2;
        };
        std::array<Scalar, 9> data{kZero, kZero, kZero,
                                   kZero, kZero, kZero,
                                   kZero, kZero, kZero};
    };
};

constexpr Vector3 operator*(Vector3 const &vec, Matrix33 const &mat)
{
    return {
        vec.x * mat(0, 0) + vec.y * mat(1, 0) + vec.z * mat(2, 0),
        vec.x * mat(0, 1) + vec.y * mat(1, 1) + vec.z * mat(2, 1),
        vec.x * mat(0, 2) + vec.y * mat(1, 2) + vec.z * mat(2, 2)};
}

inline Matrix33 operator*(Matrix33 const &matA, Matrix33 const &matB)
{
    Vector3 col0 = matB.Column(0);
    Vector3 col1 = matB.Column(1);
    Vector3 col2 = matB.Column(2);
    Vector3 row0 = matA.row0;
    Vector3 row1 = matA.row1;
    Vector3 row2 = matA.row2;
    return {
        row0.Dot(col0), row0.Dot(col1), row0.Dot(col2),
        row1.Dot(col0), row1.Dot(col1), row1.Dot(col2),
        row2.Dot(col0), row2.Dot(col1), row2.Dot(col2)};
}

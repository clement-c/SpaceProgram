#pragma once
#include <immintrin.h>
#include "Constants.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix33.hpp"

#include "../Lib.hpp"

struct Matrix44
{
    static constexpr Matrix44 Identity()
    {
        return {
            kOne, kZero, kZero, kZero,
            kZero, kOne, kZero, kZero,
            kZero, kZero, kOne, kZero,
            kZero, kZero, kZero, kOne};
    }
    static constexpr Matrix44 FromPosition(Vector4 const &pos)
    {
        return {
            kOne, kZero, kZero, kZero,
            kZero, kOne, kZero, kZero,
            kZero, kZero, kOne, kZero,
            pos.x, pos.y, pos.z, pos.w};
    }
    static constexpr Matrix44 FromPosition(Scalar pos_x, Scalar pos_y, Scalar pos_z)
    {
        return {
            kOne, kZero, kZero, kZero,
            kZero, kOne, kZero, kZero,
            kZero, kZero, kOne, kZero,
            pos_x, pos_y, pos_z, kOne};
    }

    static Matrix44 AimMatrix(
        Vector4 const &source,
        Vector4 const &target,
        Vector3 upVector = Vector3::Y())
    {
        auto aimVec = (target - source).Normalized();
        auto sideVec = aimVec.Cross(upVector).Normalized();
        auto upVec = sideVec.Cross(aimVec);
        return Matrix44(Vector4(aimVec), Vector4(upVec), Vector4(sideVec), source);
    }

    constexpr Matrix44() {}
    constexpr Matrix44(Scalar diag) : data{
                                          diag, kZero, kZero, kZero,
                                          kZero, diag, kZero, kZero,
                                          kZero, kZero, diag, kZero,
                                          kZero, kZero, kZero, diag} {}
    constexpr Matrix44(Matrix44 const &m) : row0{m.row0}, row1{m.row1}, row2{m.row2}, row3{m.row3} {}
    explicit constexpr Matrix44(
        Vector4 const &rowX,
        Vector4 const &rowY,
        Vector4 const &rowZ,
        Vector4 const &pos = Vector4()) : row0{rowX}, row1{rowY}, row2{rowZ}, row3{pos} {}
    explicit constexpr Matrix44(
        Vector3 const &rowX,
        Vector3 const &rowY,
        Vector3 const &rowZ,
        Vector3 const &pos = Vector3()) : row0{rowX.x, rowX.y, rowX.z, 0.0}, row1{rowY.x, rowY.y, rowY.z, 0.0}, row2{rowZ.x, rowZ.y, rowZ.z, 0.0}, row3{pos} {}
    constexpr Matrix44(Scalar i00, Scalar i01, Scalar i02, Scalar i03,
                       Scalar i10, Scalar i11, Scalar i12, Scalar i13,
                       Scalar i20, Scalar i21, Scalar i22, Scalar i23,
                       Scalar i30, Scalar i31, Scalar i32, Scalar i33) : data{
                                                                             i00, i01, i02, i03,
                                                                             i10, i11, i12, i13,
                                                                             i20, i21, i22, i23,
                                                                             i30, i31, i32, i33} {}
    constexpr Matrix44(Matrix33 const &mat) : data{
                                                  mat.a00, mat.a01, mat.a02, kZero,
                                                  mat.a10, mat.a11, mat.a12, kZero,
                                                  mat.a20, mat.a21, mat.a22, kZero,
                                                  kZero, kZero, kZero, kOne} {}

    constexpr Matrix44(Matrix33 const &orientMat, Vector3 const &pos) : data{
                                                                            orientMat.a00, orientMat.a01, orientMat.a02, kZero,
                                                                            orientMat.a10, orientMat.a11, orientMat.a12, kZero,
                                                                            orientMat.a20, orientMat.a21, orientMat.a22, kZero,
                                                                            pos.x, pos.y, pos.z, kOne} {}

    constexpr Matrix44(Matrix33 const &orientMat, Vector4 const &pos) : data{
                                                                            orientMat.a00, orientMat.a01, orientMat.a02, kZero,
                                                                            orientMat.a10, orientMat.a11, orientMat.a12, kZero,
                                                                            orientMat.a20, orientMat.a21, orientMat.a22, kZero,
                                                                            pos.x, pos.y, pos.z, pos.w} {}


    constexpr operator Matrix33() const
    {
        return Matrix33{a00, a01, a02, a10, a11, a12, a20, a21, a22}; // NOT CARTESIAN
    }

    inline Scalar &operator()(uint32_t row, uint32_t comp)
    {
        return data[row * 4 + comp];
    }
    constexpr Scalar const &operator()(uint32_t row, uint32_t comp) const
    {
        return data[row * 4 + comp];
    }

    inline Vector4 &operator[](uint32_t i)
    {
        return *reinterpret_cast<Vector4 *>(&data[4 * i]);
    }
    inline Vector4 const &operator[](uint32_t i) const
    {
        return *reinterpret_cast<Vector4 const *>(&data[4 * i]);
    }

    constexpr Vector4 Column(uint32_t colId) const
    {
        return Vector4(data[colId], data[4 + colId], data[8 + colId]);
    }
    bool IsOrthonormal() const noexcept;
    // void Orthonormalize();

    /* constexpr */ Matrix33 SubMatrix(uint32_t tlr, uint32_t tlc);
    constexpr Scalar Minor(uint32_t i, uint32_t j);

    Matrix44 Inverse(bool *success = nullptr) const;
    Matrix44 InverseOrthonormal() const;
    Matrix44 &InvertInPlace(bool *success = nullptr);
    Matrix44 &InvertInPlaceOrthonormal();

    Matrix44 Transposed() const;
    Matrix44 &TransposeInPlace();

    constexpr Matrix44 HadamardProduct(Matrix44 const &other) const;
    Matrix44 Multiply(Matrix44 const &other) const;   // Done
    Matrix44 &MultiplyInPlace(Matrix44 const &other); // Done

    union
    {
        struct
        {
            Scalar a00, a01, a02, a03,
                a10, a11, a12, a13,
                a20, a21, a22, a23,
                a30, a31, a32, a33;
        };
        struct
        {
            Vector4 row0, row1, row2, row3;
        };
        Scalar data[16] = {
            kOne, kZero, kZero, kZero,
            kZero, kOne, kZero, kZero,
            kZero, kZero, kOne, kZero,
            kZero, kZero, kZero, kOne};
    };
};

DLLEXPORT inline Matrix44 operator*(Matrix44 const &a, Matrix44 const &b) { return a.Multiply(b); }
inline Matrix44 &operator*=(Matrix44 &a, Matrix44 const &b) { return a.MultiplyInPlace(b); }

inline bool operator==(Matrix44 const &a, Matrix44 const &b) noexcept
{
    return a.row0 == b.row0 && a.row1 == b.row1 && a.row2 == b.row2 && a.row3 == b.row3;
}

inline Vector4 operator*(Vector4 const &p, Matrix44 const &m)
{
    return Vector4{
        p.x * m.a00 + p.y * m.a10 + p.z * m.a20 + p.w * m.a30,
        p.x * m.a01 + p.y * m.a11 + p.z * m.a21 + p.w * m.a31,
        p.x * m.a02 + p.y * m.a12 + p.z * m.a22 + p.w * m.a32,
        p.x * m.a03 + p.y * m.a13 + p.z * m.a23 + p.w * m.a33};
}

inline Vector4 &operator*=(Vector4 &p, Matrix44 const &m)
{
    p.data = {
        p.x * m.a00 + p.y * m.a10 + p.z * m.a20 + p.w * m.a30,
        p.x * m.a01 + p.y * m.a11 + p.z * m.a21 + p.w * m.a31,
        p.x * m.a02 + p.y * m.a12 + p.z * m.a22 + p.w * m.a32,
        p.x * m.a03 + p.y * m.a13 + p.z * m.a23 + p.w * m.a33};
    return p;
}

inline Vector3 operator*(Vector3 const &p, Matrix44 const &m)
{
    return Vector3{
        p.x * m.a00 + p.y * m.a10 + p.z * m.a20,
        p.x * m.a01 + p.y * m.a11 + p.z * m.a21,
        p.x * m.a02 + p.y * m.a12 + p.z * m.a22};
}

inline Vector3 &operator*=(Vector3 &v, Matrix44 const &m)
{
    v.data = {
        v.x * m.a00 + v.y * m.a10 + v.z * m.a20,
        v.x * m.a01 + v.y * m.a11 + v.z * m.a21,
        v.x * m.a02 + v.y * m.a12 + v.z * m.a22};
    return v;
}

inline Matrix44 operator~(Matrix44 const &m)
{
    return m.Inverse();
}

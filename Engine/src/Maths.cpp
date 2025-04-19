#include "Engine/Core/Maths/MathsIO.hpp"
#include "Engine/Core/Maths/Vector3.hpp"
#include "Engine/Core/Maths/Matrix44.hpp"
#include <algorithm>

// ====================== VECTOR3 ======================

// constexpr Vector3::Vector3(Scalar xx, Scalar yy, Scalar zz) : x{xx}, y{yy}, z{zz} {}

constexpr Vector3::operator Vector4() const
{
    return Vector4(x, y, z, kOne);
}

constexpr Scalar &Vector3::operator[](uint32_t i)
{
    return data[i];
}

Vector3 &Vector3::operator+=(Vector3 const &other) noexcept
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3 &Vector3::operator-=(Vector3 const &other) noexcept
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3 &Vector3::operator*=(Scalar scale) noexcept
{
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Vector3 &Vector3::operator/=(Scalar scale)
{
    x /= scale;
    y /= scale;
    z /= scale;
    return *this;
}

constexpr Vector3 Vector3::Scaled(Scalar const scale) const
{
    return Vector3{x * scale, y * scale, z * scale};
}

inline Vector3 &Vector3::Scale(Scalar const scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

constexpr Vector3 Vector3::Negated() const
{
    return Scaled(static_cast<Scalar>(-1.0));
}

inline Vector3 &Vector3::Negate()
{
    return Scale(static_cast<Scalar>(-1.0));
}

constexpr Scalar Vector3::Dot(Vector3 const &other) const noexcept(true)
{
    return (x * other.x + y * other.y + z * other.z);
}

constexpr Vector3 Vector3::Cross(Vector3 const &other) const noexcept
{
    return Vector3(
        y * other.z - other.y * z, z * other.x - other.z * x, x * other.y - y * other.x);
}

constexpr Scalar Vector3::MagnitudeSquared() const
{
    return Dot(*this);
}

inline Scalar Vector3::Magnitude() const noexcept
{
    return std::sqrt(MagnitudeSquared());
}

Vector3 &Vector3::Normalize()
{
    Scalar r = (Scalar)1.0f / Magnitude();
    x *= r;
    y *= r;
    z *= r;
    return *this;
}

inline Vector3 Vector3::Normalized() const
{
    return Vector3(*this).Normalize();
}

inline Vector3 Vector3::Project(Vector3 const &onto) const
{
    return onto.Scaled((*this).Dot(onto) / onto.MagnitudeSquared());
}

// ====================== VECTOR4 ======================

constexpr Vector4::Vector4(Scalar xx, Scalar yy, Scalar zz, Scalar ww) : x{xx}, y{yy}, z{zz}, w{ww} {}
constexpr Vector4::Vector4(Vector3 const &vec, Scalar w_) : x{vec.x}, y{vec.y}, z{vec.z}, w{w_} {}

Vector4 &Vector4::operator=(Vector3 const &vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = kOne;
    return *this;
}

Vector4 &Vector4::Homogenize()
{
    if (w != kZero)
    {
        auto ratio = kOne / w;
        x *= ratio;
        y *= ratio;
        z *= ratio;
        w = kOne;
    }
    return *this;
}

constexpr Vector3 Vector4::Cartesian() const
{
    if (w != kZero)
    {
        auto ratio = kOne / w;
        return Vector3{x * ratio, y * ratio, z * ratio};
    }
    return Vector3{x, y, z};
}

constexpr Vector4::operator Vector3() const
{
    return Vector3{x, y, z}; // NOT CARTESIAN
}

// ====================== MATRIX44 ======================

bool Matrix44::IsOrthonormal() const noexcept
{
    return fabs(kOne - fabs(Vector3(row0).Dot(Vector3(row1)))) < kEpsilon && fabs(kOne - fabs(Vector3(row1).Dot(Vector3(row2))));
}

constexpr Matrix44 Matrix44::HadamardProduct(Matrix44 const &other) const
{
    return {
        a00 * other.a00, a01 * other.a01, a02 * other.a02, a03 * other.a03,
        a10 * other.a10, a11 * other.a11, a12 * other.a12, a13 * other.a13,
        a20 * other.a20, a21 * other.a21, a22 * other.a22, a23 * other.a23,
        a30 * other.a30, a31 * other.a31, a32 * other.a32, a33 * other.a33};
}

Matrix33 Matrix44::SubMatrix(uint32_t tlr, uint32_t tlc)
{
    auto const &m = (*this);
    return {
        m((tlr + 0) % 4, ((tlc + 0) % 4)),
        m((tlr + 0) % 4, ((tlc + 1) % 4)),
        m((tlr + 0) % 4, ((tlc + 2) % 4)),
        m((tlr + 1) % 4, ((tlc + 0) % 4)),
        m((tlr + 1) % 4, ((tlc + 1) % 4)),
        m((tlr + 1) % 4, ((tlc + 2) % 4)),
        m((tlr + 2) % 4, ((tlc + 0) % 4)),
        m((tlr + 2) % 4, ((tlc + 1) % 4)),
        m((tlr + 2) % 4, ((tlc + 2) % 4))};
}

constexpr Scalar Matrix44::Minor(uint32_t i, uint32_t j)
{
    auto const &m = (*this);
    return Matrix33{
        m((i + 1) % 4, ((j + 1) % 4)),
        m((i + 1) % 4, ((j + 2) % 4)),
        m((i + 1) % 4, ((j + 3) % 4)),
        m((i + 2) % 4, ((j + 1) % 4)),
        m((i + 2) % 4, ((j + 2) % 4)),
        m((i + 2) % 4, ((j + 3) % 4)),
        m((i + 3) % 4, ((j + 1) % 4)),
        m((i + 3) % 4, ((j + 2) % 4)),
        m((i + 3) % 4, ((j + 3) % 4))}
        .Determinant();
}

Matrix44 Matrix44::Inverse(bool *success) const
{
    auto m = *this;
    m.InvertInPlace(success);
    return m;
}

Matrix44 &Matrix44::InvertInPlace(bool *success)
{
    auto &m = *this;
    Matrix44 minorsMatrix{
        Minor(0, 0), Minor(0, 1), Minor(0, 2), Minor(0, 3),
        Minor(1, 0), Minor(1, 1), Minor(1, 2), Minor(1, 3),
        Minor(2, 0), Minor(2, 1), Minor(2, 2), Minor(2, 3),
        Minor(3, 0), Minor(3, 1), Minor(3, 2), Minor(3, 3)};
    Matrix44 cofactorsMatrix = minorsMatrix.HadamardProduct({+1.0, -1.0, +1.0, -1.0,
                                                             -1.0, +1.0, -1.0, +1.0,
                                                             +1.0, -1.0, +1.0, -1.0,
                                                             -1.0, +1.0, -1.0, +1.0});
    Matrix44 adjoint = cofactorsMatrix.Transposed();

    Scalar determinant = m(0, 0) * cofactorsMatrix(0, 0) +
                         m(0, 1) * cofactorsMatrix(0, 1) +
                         m(0, 2) * cofactorsMatrix(0, 2) +
                         m(0, 3) * cofactorsMatrix(0, 3);

    if (nullptr != success && determinant < kEpsilon)
        *success = false;

    Scalar detInv = static_cast<Scalar>(1.0) / determinant;
    m(0, 0) = adjoint(0, 0) * detInv;
    m(0, 1) = adjoint(0, 1) * detInv;
    m(0, 2) = adjoint(0, 2) * detInv;
    m(0, 3) = adjoint(0, 3) * detInv;
    m(1, 0) = adjoint(1, 0) * detInv;
    m(1, 1) = adjoint(1, 1) * detInv;
    m(1, 2) = adjoint(1, 2) * detInv;
    m(1, 3) = adjoint(1, 3) * detInv;
    m(2, 0) = adjoint(2, 0) * detInv;
    m(2, 1) = adjoint(2, 1) * detInv;
    m(2, 2) = adjoint(2, 2) * detInv;
    m(2, 3) = adjoint(2, 3) * detInv;
    m(3, 0) = adjoint(3, 0) * detInv;
    m(3, 1) = adjoint(3, 1) * detInv;
    m(3, 2) = adjoint(3, 2) * detInv;
    m(3, 3) = adjoint(3, 3) * detInv;

    if (nullptr != success)
        *success = true;
    return *this;
}

Matrix44 Matrix44::InverseOrthonormal() const
{
    return Matrix44{
        a00, a10, a20, kZero,
        a01, a11, a21, kZero,
        a02, a12, a22, kZero,
        kMinusOne * (a30 * a00 + a31 * a01 + a32 * a02),
        kMinusOne * (a30 * a10 + a31 * a11 + a32 * a12),
        kMinusOne * (a30 * a20 + a31 * a21 + a32 * a22),
        kOne};
}

Matrix44 &Matrix44::InvertInPlaceOrthonormal()
{
    // 00 01 02 03
    // 04 05 06 07
    // 08 09 10 11
    // 12 13 14 15
    std::swap(data[1], data[4]);
    std::swap(data[2], data[8]);
    std::swap(data[6], data[9]);

    Vector3 newPos{kMinusOne * (a30 * a00 + a31 * a10 + a32 * a20),
                   kMinusOne * (a30 * a01 + a31 * a11 + a32 * a21),
                   kMinusOne * (a30 * a02 + a31 * a12 + a32 * a22)};
    a30 = newPos.x;
    a31 = newPos.y;
    a32 = newPos.z;
    a33 = static_cast<Scalar>(1.0);
    return *this;
}

Matrix44 &Matrix44::MultiplyInPlace(Matrix44 const &other)
{
    a00 = a00 * other.a00 + a01 * other.a10 + a02 * other.a20 + a03 * other.a30;
    a01 = a00 * other.a01 + a01 * other.a11 + a02 * other.a21 + a03 * other.a31;
    a02 = a00 * other.a02 + a01 * other.a12 + a02 * other.a22 + a03 * other.a32;
    a03 = a00 * other.a03 + a01 * other.a13 + a02 * other.a23 + a03 * other.a33;

    a10 = a10 * other.a00 + a11 * other.a10 + a12 * other.a20 + a13 * other.a30;
    a11 = a10 * other.a01 + a11 * other.a11 + a12 * other.a21 + a13 * other.a31;
    a12 = a10 * other.a02 + a11 * other.a12 + a12 * other.a22 + a13 * other.a32;
    a13 = a10 * other.a03 + a11 * other.a13 + a12 * other.a23 + a13 * other.a33;

    a20 = a20 * other.a00 + a21 * other.a10 + a22 * other.a20 + a23 * other.a30;
    a21 = a20 * other.a01 + a21 * other.a11 + a22 * other.a21 + a23 * other.a31;
    a22 = a20 * other.a02 + a21 * other.a12 + a22 * other.a22 + a23 * other.a32;
    a23 = a20 * other.a03 + a21 * other.a13 + a22 * other.a23 + a23 * other.a33;

    a30 = a30 * other.a00 + a31 * other.a10 + a32 * other.a20 + a33 * other.a30;
    a31 = a30 * other.a01 + a31 * other.a11 + a32 * other.a21 + a33 * other.a31;
    a32 = a30 * other.a02 + a31 * other.a12 + a32 * other.a22 + a33 * other.a32;
    a33 = a30 * other.a03 + a31 * other.a13 + a32 * other.a23 + a33 * other.a33;

    return *this;
}

Matrix44 Matrix44::Multiply(Matrix44 const &other) const
{
    return Matrix44{
        a00 * other.a00 + a01 * other.a10 + a02 * other.a20 + a03 * other.a30,
        a00 * other.a01 + a01 * other.a11 + a02 * other.a21 + a03 * other.a31,
        a00 * other.a02 + a01 * other.a12 + a02 * other.a22 + a03 * other.a32,
        a00 * other.a03 + a01 * other.a13 + a02 * other.a23 + a03 * other.a33,

        a10 * other.a00 + a11 * other.a10 + a12 * other.a20 + a13 * other.a30,
        a10 * other.a01 + a11 * other.a11 + a12 * other.a21 + a13 * other.a31,
        a10 * other.a02 + a11 * other.a12 + a12 * other.a22 + a13 * other.a32,
        a10 * other.a03 + a11 * other.a13 + a12 * other.a23 + a13 * other.a33,

        a20 * other.a00 + a21 * other.a10 + a22 * other.a20 + a23 * other.a30,
        a20 * other.a01 + a21 * other.a11 + a22 * other.a21 + a23 * other.a31,
        a20 * other.a02 + a21 * other.a12 + a22 * other.a22 + a23 * other.a32,
        a20 * other.a03 + a21 * other.a13 + a22 * other.a23 + a23 * other.a33,

        a30 * other.a00 + a31 * other.a10 + a32 * other.a20 + a33 * other.a30,
        a30 * other.a01 + a31 * other.a11 + a32 * other.a21 + a33 * other.a31,
        a30 * other.a02 + a31 * other.a12 + a32 * other.a22 + a33 * other.a32,
        a30 * other.a03 + a31 * other.a13 + a32 * other.a23 + a33 * other.a33};
}

Matrix44 Matrix44::Transposed() const
{
    return Matrix44{
        data[0], data[4], data[8], data[12],
        data[1], data[5], data[9], data[13],
        data[2], data[6], data[10], data[14],
        data[3], data[7], data[11], data[15]};
}

Matrix44 &Matrix44::TransposeInPlace()
{
    std::swap(data[1], data[4]);
    std::swap(data[2], data[8]);
    std::swap(data[3], data[12]);
    std::swap(data[6], data[9]);
    std::swap(data[7], data[13]);
    std::swap(data[11], data[14]);
    return *this;
}

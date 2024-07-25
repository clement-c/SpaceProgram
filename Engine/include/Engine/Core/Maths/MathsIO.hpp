#pragma once
#include <iostream>

#include "AABB.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix33.hpp"
#include "Matrix44.hpp"

inline std::ostream &operator<<(std::ostream &os, Vector2 const &vec)
{
    return os << '{' << vec.x << ", " << vec.y << '}';
}

inline std::ostream &operator<<(std::ostream &os, Vector3 const &vec)
{
    return os << '{' << vec.x << ", " << vec.y << ", " << vec.z << '}';
}

inline std::ostream &operator<<(std::ostream &os, Vector4 const &vec)
{
    return os << '{' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << '}';
}

inline std::ostream &operator<<(std::ostream &os, Matrix33 const &mat)
{
    return os << "{ " << mat.row0 << ", " << mat.row1 << ", " << mat.row2 << " }";
}

inline std::ostream &operator<<(std::ostream &os, Matrix44 const &mat)
{
    return os << "{ " << mat.row0 << ", " << mat.row1 << ", " << mat.row2 << ", " << mat.row3 << " }";
}

inline std::ostream &operator<<(std::ostream &os, AABB const &bb)
{
    return os << "{ " << bb.Min << ", " << bb.Max << " }";
}

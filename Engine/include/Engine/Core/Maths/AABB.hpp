#pragma once
#include <iostream>

#include "Vector4.hpp"

struct AABB
{
    Vector4 Min, Max;

    AABB() = default;
    AABB(Vector4 ptA, Vector4 ptB)
    {
        Min.x = (ptA.x < ptB.x ? ptA.x : ptB.x);
        Min.y = (ptA.y < ptB.y ? ptA.y : ptB.y);
        Min.z = (ptA.z < ptB.z ? ptA.z : ptB.z);
        Max.x = (ptA.x >= ptB.x ? ptA.x : ptB.x);
        Max.y = (ptA.y >= ptB.y ? ptA.y : ptB.y);
        Max.z = (ptA.z >= ptB.z ? ptA.z : ptB.z);
    }

    Scalar GetSize() const noexcept
    {
        return (Max - Min).Magnitude();
    }

    Vector4 GetCenter() const noexcept
    {
        return Min + (Max - Min) * 0.5;
    }

    inline AABB& Expand(Vector4 const& point)
    {
        Min.x = (point.x < Min.x ? point.x : Min.x);
        Min.y = (point.y < Min.y ? point.y : Min.y);
        Min.z = (point.z < Min.z ? point.z : Min.z);
        Max.x = (point.x >= Max.x ? point.x : Max.x);
        Max.y = (point.y >= Max.y ? point.y : Max.y);
        Max.z = (point.z >= Max.z ? point.z : Max.z);
        return *this;
    }

    inline bool Contains(Vector3 const& pt)
    {
        return pt.x >= Min.x && pt.x <= Max.x && pt.y >= Min.y && pt.y <= Max.y && pt.z >= Min.z && pt.z <= Max.z;
    }

    inline bool Contains(Vector4 const& pt)
    {
        return Contains(Vector3(pt));
    }

    inline bool Contains(AABB const& bb)
    {
        return Contains(bb.Min) && Contains(bb.Max);
    }

};

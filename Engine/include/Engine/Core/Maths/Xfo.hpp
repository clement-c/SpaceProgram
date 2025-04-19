#pragma once
#include "Quaternion.hpp"
#include "Vector4.hpp"
#include "Vector3.hpp"

struct Xfo
{
    Quaternion Rotation() const noexcept;
 
    Vector4 Position() const noexcept;
 
    Vector3 Scale() const noexcept
    {
        return m_scale;
    }

public:
    Quaternion m_rotation;
    Vector4 m_position;
    Vector3 m_scale;
};

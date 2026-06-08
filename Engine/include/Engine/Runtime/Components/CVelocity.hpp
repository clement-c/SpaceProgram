#pragma once
#include "Core/Maths/Vector3.hpp"

namespace Engine::ECS {

struct CVelocity
{
    Vector3 velocity = Vector3::Zero();

    CVelocity() = default;
    CVelocity(float x, float y, float z)
        : velocity(x, y, z) {}

};

}
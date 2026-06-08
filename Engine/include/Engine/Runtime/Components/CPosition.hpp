#pragma once

#include "Core/Lib.hpp"
#include "Core/Maths/Vector4.hpp"

#include <cstdint>

namespace Engine::ECS {

struct CPosition {
    Vector4 position = Vector4::Zero();

    CPosition() = default;
    CPosition(float x, float y, float z)
        : position(x, y, z) {}

};

} // namespace Engine::ECS

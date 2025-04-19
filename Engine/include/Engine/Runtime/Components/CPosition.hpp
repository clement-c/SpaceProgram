#pragma once

#include "Core/Lib.hpp"
#include "Core/Maths/Vector4.hpp"

#include <cstdint>

namespace Engine::Runtime::ECS {

struct CPosition {
    Vector4 position = Vector4::Zero();

    CPosition() = default;

    CPosition(float x, float y, float z)
        : position(x, y, z) {}

    void SetPosition(Vector4 const &newPosition) {
        position = newPosition;
    }

};

} // namespace Engine::Runtime::ECS
#pragma once

namespace Engine::ECS::Components {

/**
 * @brief Simple 3D position component
 */
struct Position {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    
    Position() = default;
    Position(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

/**
 * @brief Simple 3D velocity component
 */
struct Velocity {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    
    Velocity() = default;
    Velocity(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

/**
 * @brief Rotation component using Euler angles
 */
struct Rotation {
    float pitch = 0.0f; // X-axis rotation
    float yaw = 0.0f;   // Y-axis rotation
    float roll = 0.0f;  // Z-axis rotation
    
    Rotation() = default;
    Rotation(float p, float y, float r) : pitch(p), yaw(y), roll(r) {}
};

/**
 * @brief Simple name tag component
 */
struct Name {
    char name[64] = {0};
    
    Name() = default;
    Name(const char* n) {
        size_t len = 0;
        while (n[len] && len < 63) {
            name[len] = n[len];
            len++;
        }
        name[len] = '\0';
    }
};

} // namespace Engine::ECS::Components

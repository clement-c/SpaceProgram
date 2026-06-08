#pragma once
#include "Engine/Core/ECS/System.hpp"

class PhysicsSystem : public System
{
public:
    bool Update(float deltaTime) override
    {
        // for (Entity entity : m_entities) {
        //     auto& pos = m_world->GetComponent<Position>(entity);
        //     auto& vel = m_world->GetComponent<Velocity>(entity);

        //     pos.x += vel.x * deltaTime;
        //     pos.y += vel.y * deltaTime;
        //     pos.z += vel.z * deltaTime;
        // }
    }

    const char *GetName() const override
    {
        return "PhysicsSystem";
    }

    // void SetWorld(World* world) { m_world = world; }

private:
    // World* m_world = nullptr;
};
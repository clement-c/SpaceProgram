#include <Engine/ECS/ECS.hpp>
#include <Engine/ECS/Components.hpp>
#include <Engine/ECS/ECSDebugger.hpp>
#include <iostream>
#include <cmath>

using namespace Engine::ECS;
using namespace Engine::ECS::Components;

/**
 * @brief Example physics system that updates positions based on velocities
 */
class PhysicsSystem : public System {
public:
    void Init() override {
        std::cout << "[PhysicsSystem] Initialized" << std::endl;
    }

    void Update(float deltaTime) override {
        // Update positions based on velocities
        for (Entity entity : m_entities) {
            auto& pos = m_world->GetComponent<Position>(entity);
            auto& vel = m_world->GetComponent<Velocity>(entity);
            
            pos.x += vel.x * deltaTime;
            pos.y += vel.y * deltaTime;
            pos.z += vel.z * deltaTime;
        }
    }

    void Shutdown() override {
        std::cout << "[PhysicsSystem] Shutdown" << std::endl;
    }

    const char* GetName() const override {
        return "PhysicsSystem";
    }

    void SetWorld(World* world) {
        m_world = world;
    }

private:
    World* m_world = nullptr;
};

/**
 * @brief Example rotation system that updates rotations
 */
class RotationSystem : public System {
public:
    void Init() override {
        std::cout << "[RotationSystem] Initialized" << std::endl;
    }

    void Update(float deltaTime) override {
        // Simple rotation around Y axis
        for (Entity entity : m_entities) {
            auto& rot = m_world->GetComponent<Rotation>(entity);
            rot.yaw += rotationSpeed * deltaTime;
            
            // Wrap around
            if (rot.yaw > 360.0f) {
                rot.yaw -= 360.0f;
            }
        }
    }

    void Shutdown() override {
        std::cout << "[RotationSystem] Shutdown" << std::endl;
    }

    const char* GetName() const override {
        return "RotationSystem";
    }

    void SetWorld(World* world) {
        m_world = world;
    }

    float rotationSpeed = 45.0f; // degrees per second

private:
    World* m_world = nullptr;
};

/**
 * @brief Example debug print system
 */
class DebugPrintSystem : public System {
public:
    void Update(float deltaTime) override {
        updateTimer += deltaTime;
        
        // Print every second
        if (updateTimer >= 1.0f) {
            updateTimer = 0.0f;
            
            std::cout << "\n[DebugPrintSystem] Entity Status:" << std::endl;
            for (Entity entity : m_entities) {
                auto& name = m_world->GetComponent<Name>(entity);
                auto& pos = m_world->GetComponent<Position>(entity);
                
                std::cout << "  " << name.name << ": pos(" 
                          << pos.x << ", " << pos.y << ", " << pos.z << ")" 
                          << std::endl;
            }
        }
    }

    const char* GetName() const override {
        return "DebugPrintSystem";
    }

    void SetWorld(World* world) {
        m_world = world;
    }

private:
    World* m_world = nullptr;
    float updateTimer = 0.0f;
};

/**
 * @brief Example ECS usage
 */
int main() {
    std::cout << "=== ECS Example ===" << std::endl;
    
    // Create the ECS world
    World world;
    
    // Register components
    world.RegisterComponent<Position>();
    world.RegisterComponent<Velocity>();
    world.RegisterComponent<Rotation>();
    world.RegisterComponent<Name>();
    
    // Register and configure PhysicsSystem
    auto physicsSystem = world.RegisterSystem<PhysicsSystem>();
    physicsSystem->SetWorld(&world);
    {
        Signature signature;
        signature.set(world.GetComponentType<Position>());
        signature.set(world.GetComponentType<Velocity>());
        world.SetSystemSignature<PhysicsSystem>(signature);
    }
    
    // Register and configure RotationSystem
    auto rotationSystem = world.RegisterSystem<RotationSystem>();
    rotationSystem->SetWorld(&world);
    {
        Signature signature;
        signature.set(world.GetComponentType<Rotation>());
        world.SetSystemSignature<RotationSystem>(signature);
    }
    
    // Register and configure DebugPrintSystem
    auto debugPrintSystem = world.RegisterSystem<DebugPrintSystem>();
    debugPrintSystem->SetWorld(&world);
    {
        Signature signature;
        signature.set(world.GetComponentType<Position>());
        signature.set(world.GetComponentType<Name>());
        world.SetSystemSignature<DebugPrintSystem>(signature);
    }
    
    // Create some entities
    std::cout << "\nCreating entities..." << std::endl;
    
    // Entity 1: Moving box
    Entity box = world.CreateEntity();
    world.AddComponent(box, Position{0.0f, 0.0f, 0.0f});
    world.AddComponent(box, Velocity{1.0f, 0.5f, 0.0f});
    world.AddComponent(box, Rotation{0.0f, 0.0f, 0.0f});
    world.AddComponent(box, Name{"Moving Box"});
    
    // Entity 2: Static sphere (no velocity, just rotation)
    Entity sphere = world.CreateEntity();
    world.AddComponent(sphere, Position{5.0f, 2.0f, 0.0f});
    world.AddComponent(sphere, Rotation{0.0f, 0.0f, 0.0f});
    world.AddComponent(sphere, Name{"Rotating Sphere"});
    
    // Entity 3: Fast particle
    Entity particle = world.CreateEntity();
    world.AddComponent(particle, Position{-5.0f, 0.0f, 0.0f});
    world.AddComponent(particle, Velocity{3.0f, -1.0f, 0.5f});
    world.AddComponent(particle, Name{"Fast Particle"});
    
    std::cout << "Created " << world.GetEntityCount() << " entities" << std::endl;
    
    // Initialize systems
    world.InitSystems();
    
    // Simulate a few frames
    std::cout << "\nSimulating 5 seconds..." << std::endl;
    const float deltaTime = 1.0f / 60.0f; // 60 FPS
    const int totalFrames = 5 * 60; // 5 seconds
    
    for (int frame = 0; frame < totalFrames; ++frame) {
        world.UpdateSystems(deltaTime);
    }
    
    // Print final state
    std::cout << "\n=== Final State ===" << std::endl;
    std::cout << "Box position: ";
    {
        auto& pos = world.GetComponent<Position>(box);
        std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
    }
    
    std::cout << "Sphere rotation: ";
    {
        auto& rot = world.GetComponent<Rotation>(sphere);
        std::cout << "yaw=" << rot.yaw << " degrees" << std::endl;
    }
    
    // Cleanup
    world.ShutdownSystems();
    
    std::cout << "\n=== ECS Example Complete ===" << std::endl;
    
    return 0;
}

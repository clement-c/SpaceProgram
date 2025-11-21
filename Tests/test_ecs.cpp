#include <gtest/gtest.h>
#include <Engine/ECS/ECS.hpp>
#include <Engine/ECS/Components.hpp>

using namespace Engine::ECS;
using namespace Engine::ECS::Components;

// Test entity creation and destruction
TEST(ECS, EntityCreation) {
    World world;
    
    Entity entity1 = world.CreateEntity();
    Entity entity2 = world.CreateEntity();
    
    EXPECT_NE(entity1, NULL_ENTITY);
    EXPECT_NE(entity2, NULL_ENTITY);
    EXPECT_NE(entity1, entity2);
    EXPECT_EQ(world.GetEntityCount(), 2);
    
    world.DestroyEntity(entity1);
    EXPECT_EQ(world.GetEntityCount(), 1);
    
    world.DestroyEntity(entity2);
    EXPECT_EQ(world.GetEntityCount(), 0);
}

// Test component registration and manipulation
TEST(ECS, ComponentManagement) {
    World world;
    world.RegisterComponent<Position>();
    world.RegisterComponent<Velocity>();
    
    Entity entity = world.CreateEntity();
    
    // Add components
    world.AddComponent(entity, Position{1.0f, 2.0f, 3.0f});
    world.AddComponent(entity, Velocity{0.5f, 0.5f, 0.5f});
    
    // Check components exist
    EXPECT_TRUE(world.HasComponent<Position>(entity));
    EXPECT_TRUE(world.HasComponent<Velocity>(entity));
    
    // Check component values
    auto& pos = world.GetComponent<Position>(entity);
    EXPECT_FLOAT_EQ(pos.x, 1.0f);
    EXPECT_FLOAT_EQ(pos.y, 2.0f);
    EXPECT_FLOAT_EQ(pos.z, 3.0f);
    
    // Modify component
    pos.x = 10.0f;
    EXPECT_FLOAT_EQ(world.GetComponent<Position>(entity).x, 10.0f);
    
    // Remove component
    world.RemoveComponent<Velocity>(entity);
    EXPECT_FALSE(world.HasComponent<Velocity>(entity));
    EXPECT_TRUE(world.HasComponent<Position>(entity));
}

// Test system that updates positions based on velocities
class TestPhysicsSystem : public System {
public:
    void Update(float deltaTime) override {
        for (Entity entity : m_entities) {
            auto& pos = m_world->GetComponent<Position>(entity);
            auto& vel = m_world->GetComponent<Velocity>(entity);
            
            pos.x += vel.x * deltaTime;
            pos.y += vel.y * deltaTime;
            pos.z += vel.z * deltaTime;
        }
    }
    
    const char* GetName() const override {
        return "TestPhysicsSystem";
    }
    
    void SetWorld(World* world) {
        m_world = world;
    }
    
private:
    World* m_world = nullptr;
};

// Test system execution
TEST(ECS, SystemExecution) {
    World world;
    world.RegisterComponent<Position>();
    world.RegisterComponent<Velocity>();
    
    // Register system
    auto physicsSystem = world.RegisterSystem<TestPhysicsSystem>();
    physicsSystem->SetWorld(&world);
    
    Signature signature;
    signature.set(world.GetComponentType<Position>());
    signature.set(world.GetComponentType<Velocity>());
    world.SetSystemSignature<TestPhysicsSystem>(signature);
    
    // Create entity with components
    Entity entity = world.CreateEntity();
    world.AddComponent(entity, Position{0.0f, 0.0f, 0.0f});
    world.AddComponent(entity, Velocity{1.0f, 2.0f, 3.0f});
    
    // Verify entity is in system
    EXPECT_EQ(physicsSystem->m_entities.size(), 1);
    EXPECT_TRUE(physicsSystem->m_entities.find(entity) != physicsSystem->m_entities.end());
    
    // Update system
    world.UpdateSystems(1.0f);
    
    // Check position was updated
    auto& pos = world.GetComponent<Position>(entity);
    EXPECT_FLOAT_EQ(pos.x, 1.0f);
    EXPECT_FLOAT_EQ(pos.y, 2.0f);
    EXPECT_FLOAT_EQ(pos.z, 3.0f);
    
    // Update again
    world.UpdateSystems(0.5f);
    EXPECT_FLOAT_EQ(pos.x, 1.5f);
    EXPECT_FLOAT_EQ(pos.y, 3.0f);
    EXPECT_FLOAT_EQ(pos.z, 4.5f);
}

// Test system filtering based on signatures
TEST(ECS, SystemFiltering) {
    World world;
    world.RegisterComponent<Position>();
    world.RegisterComponent<Velocity>();
    world.RegisterComponent<Rotation>();
    
    auto physicsSystem = world.RegisterSystem<TestPhysicsSystem>();
    physicsSystem->SetWorld(&world);
    
    // System requires both Position and Velocity
    Signature signature;
    signature.set(world.GetComponentType<Position>());
    signature.set(world.GetComponentType<Velocity>());
    world.SetSystemSignature<TestPhysicsSystem>(signature);
    
    // Entity with Position and Velocity - should match
    Entity entity1 = world.CreateEntity();
    world.AddComponent(entity1, Position{});
    world.AddComponent(entity1, Velocity{});
    
    // Entity with only Position - should not match
    Entity entity2 = world.CreateEntity();
    world.AddComponent(entity2, Position{});
    
    // Entity with Position, Velocity, and Rotation - should match
    Entity entity3 = world.CreateEntity();
    world.AddComponent(entity3, Position{});
    world.AddComponent(entity3, Velocity{});
    world.AddComponent(entity3, Rotation{});
    
    // Check system has correct entities
    EXPECT_EQ(physicsSystem->m_entities.size(), 2);
    EXPECT_TRUE(physicsSystem->m_entities.find(entity1) != physicsSystem->m_entities.end());
    EXPECT_FALSE(physicsSystem->m_entities.find(entity2) != physicsSystem->m_entities.end());
    EXPECT_TRUE(physicsSystem->m_entities.find(entity3) != physicsSystem->m_entities.end());
}

// Test entity recycling
TEST(ECS, EntityRecycling) {
    World world;
    
    Entity entity1 = world.CreateEntity();
    Entity entity2 = world.CreateEntity();
    
    world.DestroyEntity(entity1);
    
    // Creating a new entity should reuse entity1's ID
    Entity entity3 = world.CreateEntity();
    EXPECT_EQ(entity3, entity1);
    EXPECT_EQ(world.GetEntityCount(), 2);
}

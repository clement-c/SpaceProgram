#pragma once

/**
 * @file ECS.hpp
 * @brief Main header for the Entity-Component-System framework
 * 
 * This is an efficient ECS implementation with the following features:
 * - Cache-friendly component storage using packed arrays
 * - Entity recycling with version numbers
 * - Signature-based system filtering
 * - Serial system execution (designed for future parallel execution with dependencies)
 * 
 * Usage example:
 * @code
 * using namespace Engine::ECS;
 * 
 * // Create world
 * World world;
 * 
 * // Register components
 * world.RegisterComponent<Position>();
 * world.RegisterComponent<Velocity>();
 * 
 * // Register and configure systems
 * auto physicsSystem = world.RegisterSystem<PhysicsSystem>();
 * Signature physicsSignature;
 * physicsSignature.set(world.GetComponentType<Position>());
 * physicsSignature.set(world.GetComponentType<Velocity>());
 * world.SetSystemSignature<PhysicsSystem>(physicsSignature);
 * 
 * // Create entities
 * Entity entity = world.CreateEntity();
 * world.AddComponent(entity, Position{0.0f, 0.0f, 0.0f});
 * world.AddComponent(entity, Velocity{1.0f, 0.0f, 0.0f});
 * 
 * // Game loop
 * world.InitSystems();
 * while (running) {
 *     world.UpdateSystems(deltaTime);
 * }
 * world.ShutdownSystems();
 * @endcode
 */

#include "Types.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "System.hpp"
#include "SystemManager.hpp"
#include "World.hpp"

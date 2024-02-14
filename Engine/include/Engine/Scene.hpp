#pragma once
#include <stdint.h>

#include "Core/Lib.hpp"
#include "Entity.hpp"

// Holds reference to Entities and loads/unloads them
// Knows which systems need to be executed in order for the Scene to load properly
//
// A scene can be marked for execution and drawing (to multiple targets maybe) for next game loop
/**
 * @brief Scene
 * 
 */
struct Scene
{
    /**
     * @brief Options used when creating a new scene instance
     * 
     */
    struct InitOptions
    {
        bool defer_loading = false; // 
        bool defer_allocation = false; // Will not allocate on instanciation, but on Init() or first Activate()
        uint32_t entities_size = 512u; // Number of entities expected in the scene, memory reserved when scene gets initialized
    };

    /**
     * @brief Instanciate a new Scene with the default `InitOptions`
     * 
     * @return DLLEXPORT 
     */
    DLLEXPORT Scene() : Scene(InitOptions()) {}
    Scene(InitOptions&&);

    // Add entities, for now scene manages resources,
    //   later will switch to a ResourceManager for shared entities

    DLLEXPORT Entity::EntityId AddEntity(/*resourceId*/);
    // DLLEXPORT Entity::EntityId AddEntity(Entity::Gizmo2D);
    // DLLEXPORT Entity::EntityId AddEntity(Entity::Gizmo3D);

    bool Clear(); // Remove all entities

    bool Activate(); // mark all entities as active, allocate/load them - blocking eval - if not loaded
    bool Deactivate(); // all entities are deactivated, but *not* deallocated
};

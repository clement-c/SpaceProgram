#pragma once
#include <stdint.h>

#include "Engine/Core/Lib.hpp"
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
        bool defer_loading = false;    //
        bool defer_allocation = false; // Will not allocate on instanciation, but on Init() or first Activate()
        uint32_t entities_size = 256u; // Number of entities expected in the scene, memory reserved when scene gets initialized - will be adjusted as needed
    };

    /**
     * @brief Instanciate a new Scene with the default `InitOptions`
     *
     * @return DLLEXPORT
     */
    DLLEXPORT Scene() : Scene(InitOptions()) {}
    Scene(InitOptions &&);

    bool Init();

    // Add entities

    DLLEXPORT Entity::EntityId AddEntity(/*resourceId*/);
    // DLLEXPORT Entity::EntityId AddEntity(Entity::Gizmo2D); // Static 2D entities
    // DLLEXPORT Entity::EntityId AddEntity(Entity::Gizmo3D); // Static 3D entities

    bool Clear(); // Remove all entities

    bool Activate(); // mark all entities as active, allocate/load them - blocking eval - if not loaded, doesn't mean they are all visible, Visibility system handles that on active entities
    bool Deactivate(); // all entities are deactivated, but *not* deallocated

private:
    Entity* m_entitiesPtr = nullptr;
};

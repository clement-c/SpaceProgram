#pragma once

#include "Types.hpp"
#include <set>
#include <cassert>

namespace Engine::ECS {

/**
 * @brief Base class for all systems
 * 
 * Systems operate on entities that match their required component signature
 */
class System {
public:
    virtual ~System() = default;
    
    /**
     * @brief Called once when system is initialized
     */
    virtual void Init() {}
    
    /**
     * @brief Called every frame to update the system
     * @param deltaTime Time elapsed since last update in seconds
     */
    virtual void Update(float deltaTime) = 0;
    
    /**
     * @brief Called when system is shut down
     */
    virtual void Shutdown() {}
    
    /**
     * @brief Get the name of this system for debugging
     */
    virtual const char* GetName() const = 0;
    
    /**
     * @brief Get read-only access to entities managed by this system
     */
    const std::set<Entity>& GetEntities() const {
        return m_entities;
    }

protected:
    // Set of entities that match this system's signature
    // Note: SystemManager needs access to modify this
    friend class SystemManager;
    std::set<Entity> m_entities;
};

} // namespace Engine::ECS

#pragma once

#include "Types.hpp"
#include <vector>
#include <queue>
#include <array>
#include <cassert>

namespace Engine::ECS {

/**
 * @brief Manages entity creation, destruction and versioning
 * 
 * Uses entity recycling with version numbers to efficiently reuse IDs
 */
class EntityManager {
public:
    EntityManager() {
        // Reserve space for common entity counts
        m_signatures.reserve(1024);
    }

    /**
     * @brief Create a new entity
     * @return The new entity ID
     */
    Entity CreateEntity() {
        Entity entity;
        
        if (m_freeEntities.empty()) {
            // Create new entity
            entity = m_nextEntity++;
            m_signatures.push_back(Signature{});
            m_versions.push_back(0);
        } else {
            // Reuse recycled entity
            entity = m_freeEntities.front();
            m_freeEntities.pop();
            m_signatures[entity].reset();
        }
        
        m_livingEntityCount++;
        return entity;
    }

    /**
     * @brief Destroy an entity
     * @param entity Entity to destroy
     */
    void DestroyEntity(Entity entity) {
        assert(entity < m_nextEntity && "Entity out of range");
        
        // Reset signature
        m_signatures[entity].reset();
        
        // Increment version for recycling
        m_versions[entity]++;
        
        // Add to free list
        m_freeEntities.push(entity);
        
        m_livingEntityCount--;
    }

    /**
     * @brief Set entity's component signature
     */
    void SetSignature(Entity entity, Signature signature) {
        assert(entity < m_nextEntity && "Entity out of range");
        m_signatures[entity] = signature;
    }

    /**
     * @brief Get entity's component signature
     */
    Signature GetSignature(Entity entity) const {
        assert(entity < m_nextEntity && "Entity out of range");
        return m_signatures[entity];
    }

    /**
     * @brief Get the number of living entities
     */
    uint32_t GetLivingEntityCount() const {
        return m_livingEntityCount;
    }

    /**
     * @brief Get entity version (for recycling detection)
     */
    EntityVersion GetVersion(Entity entity) const {
        assert(entity < m_nextEntity && "Entity out of range");
        return m_versions[entity];
    }

private:
    // Next entity ID to create
    Entity m_nextEntity = 1; // Start at 1, 0 is NULL_ENTITY
    
    // Queue of recycled entity IDs
    std::queue<Entity> m_freeEntities;
    
    // Signatures for each entity
    std::vector<Signature> m_signatures;
    
    // Version numbers for entity recycling
    std::vector<EntityVersion> m_versions;
    
    // Count of living entities
    uint32_t m_livingEntityCount = 0;
};

} // namespace Engine::ECS

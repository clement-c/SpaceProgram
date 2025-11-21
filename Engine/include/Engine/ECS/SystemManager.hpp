#pragma once

#include "System.hpp"
#include "Types.hpp"
#include <memory>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <cassert>

namespace Engine::ECS {

/**
 * @brief Manages system registration and execution
 */
class SystemManager {
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem() {
        const char* typeName = typeid(T).name();
        assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once");
        
        auto system = std::make_shared<T>();
        m_systems.insert({typeName, system});
        m_systemList.push_back(system);
        return system;
    }

    template<typename T>
    void SetSignature(Signature signature) {
        const char* typeName = typeid(T).name();
        assert(m_systems.find(typeName) != m_systems.end() && "System used before registered");
        m_signatures.insert({typeName, signature});
    }

    void EntityDestroyed(Entity entity) {
        // Erase a destroyed entity from all system lists
        for (auto const& pair : m_systems) {
            auto const& system = pair.second;
            system->m_entities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature) {
        // Notify each system that an entity's signature changed
        for (auto const& pair : m_systems) {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = m_signatures[type];
            
            // Entity signature matches system signature - insert into set
            if ((entitySignature & systemSignature) == systemSignature) {
                system->m_entities.insert(entity);
            }
            // Entity signature does not match system signature - erase from set
            else {
                system->m_entities.erase(entity);
            }
        }
    }

    /**
     * @brief Initialize all systems
     */
    void InitAll() {
        for (auto& system : m_systemList) {
            system->Init();
        }
    }

    /**
     * @brief Update all systems serially
     */
    void UpdateAll(float deltaTime) {
        for (auto& system : m_systemList) {
            system->Update(deltaTime);
        }
    }

    /**
     * @brief Shutdown all systems
     */
    void ShutdownAll() {
        for (auto& system : m_systemList) {
            system->Shutdown();
        }
    }

    /**
     * @brief Get all registered systems (for debugging)
     */
    const std::vector<std::shared_ptr<System>>& GetSystems() const {
        return m_systemList;
    }

private:
    // Map from system type string to a signature
    std::unordered_map<const char*, Signature> m_signatures;
    
    // Map from system type string to a system pointer
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems;
    
    // List of systems in registration order (for serial execution)
    std::vector<std::shared_ptr<System>> m_systemList;
};

} // namespace Engine::ECS

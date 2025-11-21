#pragma once

#include "Types.hpp"
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <cassert>

namespace Engine::ECS {

/**
 * @brief Base class for component arrays
 */
class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

/**
 * @brief Packed array storage for components of type T
 * 
 * Uses Structure of Arrays (SoA) layout for cache efficiency
 * Maintains dense packing for iteration performance
 */
template<typename T>
class ComponentArray : public IComponentArray {
public:
    void InsertData(Entity entity, T component) {
        assert(m_entityToIndex.find(entity) == m_entityToIndex.end() && "Component added to same entity more than once");
        
        // Put new entry at end
        size_t newIndex = m_size;
        m_entityToIndex[entity] = newIndex;
        m_indexToEntity[newIndex] = entity;
        m_componentArray[newIndex] = component;
        m_size++;
    }

    void RemoveData(Entity entity) {
        assert(m_entityToIndex.find(entity) != m_entityToIndex.end() && "Removing non-existent component");
        
        // Copy element at end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = m_entityToIndex[entity];
        size_t indexOfLastElement = m_size - 1;
        m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];
        
        // Update map to point to moved spot
        Entity entityOfLastElement = m_indexToEntity[indexOfLastElement];
        m_entityToIndex[entityOfLastElement] = indexOfRemovedEntity;
        m_indexToEntity[indexOfRemovedEntity] = entityOfLastElement;
        
        m_entityToIndex.erase(entity);
        m_indexToEntity.erase(indexOfLastElement);
        
        m_size--;
    }

    T& GetData(Entity entity) {
        assert(m_entityToIndex.find(entity) != m_entityToIndex.end() && "Retrieving non-existent component");
        return m_componentArray[m_entityToIndex[entity]];
    }

    const T& GetData(Entity entity) const {
        assert(m_entityToIndex.find(entity) != m_entityToIndex.end() && "Retrieving non-existent component");
        return m_componentArray[m_entityToIndex.at(entity)];
    }

    bool HasData(Entity entity) const {
        return m_entityToIndex.find(entity) != m_entityToIndex.end();
    }

    void EntityDestroyed(Entity entity) override {
        if (m_entityToIndex.find(entity) != m_entityToIndex.end()) {
            RemoveData(entity);
        }
    }

    // Get raw array for iteration
    T* Data() { return m_componentArray.data(); }
    const T* Data() const { return m_componentArray.data(); }
    
    size_t Size() const { return m_size; }

private:
    // Packed array of components (set to max entities for simplicity)
    std::array<T, 10000> m_componentArray;
    
    // Map from entity ID to array index
    std::unordered_map<Entity, size_t> m_entityToIndex;
    
    // Map from array index to entity ID
    std::unordered_map<size_t, Entity> m_indexToEntity;
    
    // Total size of valid entries in the array
    size_t m_size = 0;
};

/**
 * @brief Manages all component arrays
 */
class ComponentManager {
public:
    template<typename T>
    void RegisterComponent() {
        const char* typeName = typeid(T).name();
        
        assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Registering component type more than once");
        
        // Add this component type to the component type map
        m_componentTypes.insert({typeName, m_nextComponentType});
        
        // Create a ComponentArray pointer and add it to the component arrays map
        m_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
        
        m_nextComponentType++;
    }

    template<typename T>
    ComponentTypeID GetComponentType() {
        const char* typeName = typeid(T).name();
        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use");
        return m_componentTypes[typeName];
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        GetComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T& GetComponent(Entity entity) {
        return GetComponentArray<T>()->GetData(entity);
    }

    template<typename T>
    bool HasComponent(Entity entity) {
        return GetComponentArray<T>()->HasData(entity);
    }

    void EntityDestroyed(Entity entity) {
        // Notify each component array that an entity has been destroyed
        for (auto const& pair : m_componentArrays) {
            auto const& component = pair.second;
            component->EntityDestroyed(entity);
        }
    }

private:
    // Map from type string pointer to a component type
    std::unordered_map<const char*, ComponentTypeID> m_componentTypes;
    
    // Map from type string pointer to a component array
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;
    
    // The component type to be assigned to the next registered component - starting at 0
    ComponentTypeID m_nextComponentType = 0;

    // Convenience function to get the statically casted pointer to the ComponentArray of type T
    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray() {
        const char* typeName = typeid(T).name();
        assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use");
        return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
    }
};

} // namespace Engine::ECS

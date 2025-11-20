#include "Engine/Scene/Scene.hpp"
#include "Engine/Core/Logging.hpp"

Scene::Scene(InitOptions&& options)
{

}

Entity::EntityId Scene::AddEntity(AssetRef const& assetRef)
{
    CC_LOG_DEBUG("Scene::AddEntity: Adding entity from asset '{}'\n", assetRef.path);
    m_entityAssets.push_back(assetRef);
    // TODO: Create actual entity from asset reference
    return static_cast<Entity::EntityId>(m_entityAssets.size() - 1);
}

Entity::EntityId Scene::AddEntity(std::string_view path)
{
    CC_LOG_DEBUG("Scene::AddEntity: Adding entity from path '{}'\n", path);
    // Use -1 as UUID to indicate this asset hasn't been assigned a proper UUID yet
    AssetRef ref(-1, path, AssetType::Entity);
    return AddEntity(ref);
}

bool Scene::Activate(bool deferred)
{
    if (deferred)
    {
        CC_LOG_DEBUG("Scene::Activate: Deferred activation requested\n");
        // TODO: Schedule loading in background
        return true;
    }
    else
    {
        CC_LOG_DEBUG("Scene::Activate: Blocking activation - loading all entities\n");
        // TODO: Load all entity assets synchronously
        // For now, just log that we're activating
        for (const auto& asset : m_entityAssets)
        {
            CC_LOG_DEBUG("Scene::Activate: Would load entity from '{}'\n", asset.path);
        }
        return true;
    }
}

// Entity::EntityId Scene::AddEntity(Entity::Gizmo2D) { 
//     return 0;
// }

// Entity::EntityId Scene::AddEntity(Entity::Gizmo3D) {
//     return 0;
// }

#include "Engine/ResourceManager.hpp"
#include "Engine/Core/Logging.hpp"
#include <fstream>
#include <algorithm>

// ============================================================================
// Loader Implementation
// ============================================================================

Loader::Loader() : m_nextUUID(1), m_progress_cb(nullptr), m_error_cb(nullptr), m_complete_cb(nullptr)
{
}

AssetRef Loader::Enqueue(std::string_view path) noexcept
{
    // Check if asset is already queued
    for (const auto& asset : m_manifest)
    {
        if (asset.path == path)
        {
            return asset;
        }
    }
    
    // Create new asset reference
    AssetType type = DetermineAssetType(path);
    AssetRef asset(m_nextUUID++, path, type);
    m_manifest.push_back(asset);
    
    CC_LOG_DEBUG("Loader::Enqueue: Queued asset '{}' (UUID: {}, Type: {})\n", 
                 asset.path, asset.uuid, static_cast<int>(asset.type));
    
    return asset;
}

bool Loader::Load(AssetRef &asset)
{
    if (asset.status == AssetStatus::Loaded)
    {
        CC_LOG_DEBUG("Loader::Load: Asset '{}' already loaded\n", asset.path);
        return true;
    }
    
    asset.status = AssetStatus::Loading;
    bool success = LoadAsset(asset);
    
    if (success)
    {
        asset.status = AssetStatus::Loaded;
        CC_LOG_DEBUG("Loader::Load: Successfully loaded asset '{}'\n", asset.path);
    }
    else
    {
        asset.status = AssetStatus::Failed;
        CC_LOG_ERROR("Loader::Load: Failed to load asset '{}'\n", asset.path);
    }
    
    return success;
}

bool Loader::LoadAll()
{
    if (m_manifest.empty())
    {
        CC_LOG_DEBUG("Loader::LoadAll: No assets to load\n");
        if (m_complete_cb)
        {
            m_complete_cb();
        }
        return true;
    }
    
    int totalAssets = static_cast<int>(m_manifest.size());
    int loadedAssets = 0;
    
    // Count already loaded assets
    for (const auto& asset : m_manifest)
    {
        if (asset.status == AssetStatus::Loaded)
        {
            loadedAssets++;
        }
    }
    
    CC_LOG_DEBUG("Loader::LoadAll: Loading {} assets ({} already loaded)\n", totalAssets, loadedAssets);
    
    for (auto& asset : m_manifest)
    {
        if (asset.status == AssetStatus::Loaded)
        {
            continue;
        }
        
        bool success = Load(asset);
        
        if (success)
        {
            loadedAssets++;
        }
        else
        {
            // Handle error with callback
            if (m_error_cb)
            {
                bool stopLoading = m_error_cb(asset);
                if (stopLoading)
                {
                    CC_LOG_ERROR("Loader::LoadAll: Stopping load due to error callback\n");
                    return false;
                }
            }
        }
        
        // Report progress
        if (m_progress_cb)
        {
            m_progress_cb(loadedAssets, totalAssets);
        }
    }
    
    CC_LOG_DEBUG("Loader::LoadAll: Completed loading {}/{} assets\n", loadedAssets, totalAssets);
    
    if (m_complete_cb)
    {
        m_complete_cb();
    }
    
    return loadedAssets == totalAssets;
}

void Loader::OnLoadProgress(std::function<void(int, int)> &&callback)
{
    m_progress_cb = std::move(callback);
}

void Loader::OnLoadError(std::function<bool(AssetRef)> &&callback)
{
    m_error_cb = std::move(callback);
}

void Loader::OnLoadComplete(std::function<void()> &&callback)
{
    m_complete_cb = std::move(callback);
}

AssetRef const* Loader::FindAsset(UUID uuid) const
{
    for (const auto& asset : m_manifest)
    {
        if (asset.uuid == uuid)
        {
            return &asset;
        }
    }
    return nullptr;
}

AssetRef const* Loader::FindAsset(std::string_view path) const
{
    for (const auto& asset : m_manifest)
    {
        if (asset.path == path)
        {
            return &asset;
        }
    }
    return nullptr;
}

AssetType Loader::DetermineAssetType(std::string_view path) const
{
    // Extract file extension
    size_t dotPos = path.find_last_of('.');
    if (dotPos == std::string_view::npos)
    {
        return AssetType::Unknown;
    }
    
    std::string_view ext = path.substr(dotPos);
    
    // Determine type based on extension
    if (ext == ".entity")
        return AssetType::Entity;
    else if (ext == ".obj" || ext == ".fbx" || ext == ".gltf" || ext == ".glb")
        return AssetType::Model;
    else if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp" || ext == ".tga")
        return AssetType::Texture;
    else if (ext == ".mat" || ext == ".material")
        return AssetType::Material;
    else if (ext == ".glsl" || ext == ".vert" || ext == ".frag" || ext == ".shader")
        return AssetType::Shader;
    else if (ext == ".wav" || ext == ".mp3" || ext == ".ogg")
        return AssetType::Audio;
    
    return AssetType::Unknown;
}

bool Loader::LoadAsset(AssetRef &asset)
{
    // For now, just check if the file exists
    // Real implementation would load actual data based on asset type
    std::ifstream file(asset.path);
    if (!file.good())
    {
        CC_LOG_ERROR("Loader::LoadAsset: File '{}' does not exist\n", asset.path);
        return false;
    }
    
    // TODO: Implement actual asset loading based on type
    // For now, just mark as successfully validated
    switch (asset.type)
    {
        case AssetType::Entity:
            CC_LOG_DEBUG("Loader::LoadAsset: Loading Entity from '{}'\n", asset.path);
            // TODO: Parse entity file and create entity data
            break;
        case AssetType::Model:
            CC_LOG_DEBUG("Loader::LoadAsset: Loading Model from '{}'\n", asset.path);
            // TODO: Load mesh data
            break;
        case AssetType::Texture:
            CC_LOG_DEBUG("Loader::LoadAsset: Loading Texture from '{}'\n", asset.path);
            // TODO: Load texture data
            break;
        case AssetType::Material:
            CC_LOG_DEBUG("Loader::LoadAsset: Loading Material from '{}'\n", asset.path);
            // TODO: Load material data
            break;
        default:
            CC_LOG_WARNING("Loader::LoadAsset: Unknown asset type for '{}'\n", asset.path);
            break;
    }
    
    return true;
}

// ============================================================================
// ResourceManager Implementation
// ============================================================================

ResourceManager::ResourceManager() {}

Loader &ResourceManager::MainLoader()
{
    return m_mainLoader;
}

Loader &ResourceManager::NewLoader()
{
    m_loaders.push_back(std::make_unique<Loader>());
    return *m_loaders.back();
}

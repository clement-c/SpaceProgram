#pragma once
#include <stdint.h>
#include <functional>
#include <string_view>
#include <string>
#include <vector>
#include <memory>
#include "Engine/Core/Lib.hpp"

// Game resources vs scene resources

using UUID = int64_t;

enum class AssetType
{
    Unknown = 0,
    Entity,
    Model,
    Texture,
    Material,
    Shader,
    Audio
};

enum class AssetStatus
{
    Pending = 0,
    Loading,
    Loaded,
    Failed
};

struct AssetRef
{
    UUID uuid;
    std::string path;
    AssetStatus status;
    AssetType type;
    void* data; // Pointer to loaded resource data
    
    AssetRef() : uuid(0), path(""), status(AssetStatus::Pending), type(AssetType::Unknown), data(nullptr) {}
    AssetRef(UUID id, std::string_view p, AssetType t = AssetType::Unknown) 
        : uuid(id), path(p), status(AssetStatus::Pending), type(t), data(nullptr) {}
};

class Loader
{
public:
    Loader();
    
    DLLEXPORT AssetRef Enqueue(std::string_view path) noexcept;

    DLLEXPORT bool Load(AssetRef &asset);
    DLLEXPORT bool LoadAll();

    DLLEXPORT void OnLoadProgress(std::function<void(int, int)> &&callback);
    DLLEXPORT void OnLoadError(std::function<bool(AssetRef)> &&callback);
    DLLEXPORT void OnLoadComplete(std::function<void()> &&callback);
    
    DLLEXPORT AssetRef const* FindAsset(UUID uuid) const;
    DLLEXPORT AssetRef const* FindAsset(std::string_view path) const;

private:
    AssetType DetermineAssetType(std::string_view path) const;
    bool LoadAsset(AssetRef &asset);
    
    std::vector<AssetRef> m_manifest;
    UUID m_nextUUID;

    std::function<void(int, int)> m_progress_cb;
    std::function<bool(AssetRef)> m_error_cb;
    std::function<void()> m_complete_cb;
};

class ResourceManager
{
public:
    ResourceManager();

    DLLEXPORT Loader &MainLoader();
    DLLEXPORT Loader &NewLoader(); // pass options to enable format (binary, json index, etc), streams (disk, mmap, network)

    // bool PreloadBuffer(); // preload a buffer from files or memory, return as address holder

private:
    Loader m_mainLoader;
    std::vector<std::unique_ptr<Loader>> m_loaders;
};

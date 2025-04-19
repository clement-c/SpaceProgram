#pragma once
#include <stdint.h>
#include <functional>
#include <string_view>
#include <vector>
#include "Engine/Core/Lib.hpp"

// Game resources vs scene resources

using UUID = int64_t;

struct AssetRef
{
    // UUID uuid;
    // Path GetPath() const;
    // Loader::Status GetStatus() const;
    // Data::Type GetType() const;
};

class Loader
{
public:
    DLLEXPORT AssetRef Enqueue(std::string_view) noexcept;

    DLLEXPORT bool Load(AssetRef &);
    DLLEXPORT bool LoadAll();

    DLLEXPORT void OnLoadProgress(std::function<void(int, int)> &&);
    DLLEXPORT void OnLoadError(std::function<bool(AssetRef)> &&);
    DLLEXPORT void OnLoadComplete(std::function<void()> &&);

private:
    std::vector<AssetRef> m_manifest; // ?

    std::function<void(int, int)> m_progress_cb = nullptr;
    std::function<bool(AssetRef)> m_error_cb = nullptr;
    std::function<void()> m_complete_cb = nullptr;
};

class ResourceManager
{
public:
    ResourceManager();

    DLLEXPORT Loader &MainLoader();
    DLLEXPORT Loader &NewLoader(); // pass options to enable format (binary, json index, etc), streams (disk, mmap, network)

    // bool PreloadBuffer(); // preload a buffer from files or memory, return as address holder

private:
};

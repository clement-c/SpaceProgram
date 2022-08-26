#pragma once
#include <stdint.h>
#include <unordered_set>
#include "ResourceManager.hpp"
#include "System.hpp"

class Scene;

class Engine
{
public:
    struct InitOptions
    {
        std::unordered_set<uint32_t> systems_to_boot;
        uint32_t target_renderer = 0;
    };

    Engine();
    bool Initialize();
    bool Initialize(InitOptions&&);
    bool IsInitialized() const;

    System& AddSystem(/*uint32_t systemRoleId, uint32_t dependsOn*/);

    uint32_t AddRenderLayer(int depth=-1); // Set scene in layers

private:
    ResourceManager m_rscManager;
    bool m_initialized = false;
};

#pragma once
#include <stdint.h>
#include <unordered_set>

#include "Component.hpp"
#include "ResourceManager.hpp"
#include "System.hpp"

#include "Core/Lib.hpp"

class Engine
{
public:
    struct InitOptions
    {
        // Renderer
        uint32_t target_renderer_api = 0;

        // Start size of buffers and vectors, will be reserved at the start
        // uint32_t static_entities_size = 512u; // Number of static reserved at the start
        // ...

        // Core/statically-defined components to register
        std::bitset<kMaxComponents> components_to_register;
        std::bitset<16> components_groups_to_register; // ComponentsSets::kHierarchyComponents && ComponentsSets::kRenderComponents;

        // Core/statically-defined entities to register
        // ...

        // Supported input devices, joysticks, controllers, etc

        // Core devices to register / launch
        // devices = {}
        // ...
    };

    DLLEXPORT static InitOptions const kDefaultInitOptions;

    DLLEXPORT Engine();

    DLLEXPORT bool Initialize(); // Setup basic systems and their dependencies, register core datatypes
    DLLEXPORT bool Initialize(InitOptions const &);
    DLLEXPORT bool IsInitialized() const;

    ResourceManager &GetResourceManager();
    // DLLEXPORT int AddSystem();

private:
    ResourceManager m_rsc_manager;
    bool m_initialized = false;
};

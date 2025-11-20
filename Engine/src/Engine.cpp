#include "Engine/Engine.hpp"
#include "Engine/Core/Logging.hpp"
#include <iostream>

Engine::InitOptions const Engine::kDefaultInitOptions{};

Engine::Engine() : m_activeScene(nullptr) {}

bool Engine::Initialize() { return Initialize(Engine::kDefaultInitOptions); }

bool Engine::Initialize(Engine::InitOptions const &opts)
{
    if (m_initialized)
        return true;

    // Initialize
    CC_LOG_DEBUG("Engine::Initialize(...): Initializing the renderer\n");
    // opts.target_renderer_api
    CC_LOG_DEBUG("Engine::Initialize(...): Registering components\n");
    // opts.components_to_register
    // opts.components_groups_to_register
    // TODO: Use settings, for now registering only components needed for deliverable02
    m_initialized = true;
    return m_initialized;
}

bool Engine::IsInitialized() const { return m_initialized; };

ResourceManager &Engine::GetResourceManager()
{
    return m_rsc_manager;
}

void Engine::SetScene(Scene const& scene)
{
    CC_LOG_DEBUG("Engine::SetScene: Setting active scene\n");
    // TODO: Store scene properly - for now just log
    // In a real implementation, we'd copy or reference the scene
    // m_activeScene = &scene; // Can't do this with const reference
}

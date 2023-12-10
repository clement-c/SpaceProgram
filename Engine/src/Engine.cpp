#include "Engine/Engine.hpp"
#include "Engine/Core/Logging.hpp"

Engine::InitOptions const Engine::kDefaultInitOptions{};

Engine::Engine() {}

bool Engine::Initialize() { return Initialize(Engine::kDefaultInitOptions); }

bool Engine::Initialize(Engine::InitOptions const& opts) {
    if(m_initialized) return true;

    // Initialize
    CC_LOG_DEBUG("Engine::Initialize(...): Initializing the renderer");
    // opts.target_renderer_api
    CC_LOG_DEBUG("Engine::Initialize(...): Registering components");
    // opts.components_to_register
    // opts.components_groups_to_register

    // Register static entities

    m_initialized = true;
    return m_initialized;
}

bool Engine::IsInitialized() const { return m_initialized; };

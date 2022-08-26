#include "Engine/Engine.hpp"

Engine::Engine() {}

bool Engine::Initialize() { return true; }

bool Engine::IsInitialized() const { return m_initialized; };
#pragma once

#include <cstdint>
#include <bitset>

namespace Engine::ECS {

// Entity is just an ID
using Entity = uint32_t;
constexpr Entity NULL_ENTITY = 0;

// Component type ID
using ComponentTypeID = uint8_t;
constexpr ComponentTypeID MAX_COMPONENTS = 64;

// Signature to track which components an entity has
using Signature = std::bitset<MAX_COMPONENTS>;

// Version counter for entity recycling
using EntityVersion = uint16_t;

} // namespace Engine::ECS

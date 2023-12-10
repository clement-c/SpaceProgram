#pragma once
#include <bitset>
#include <limits>

using ComponentType = uint8_t;
static constexpr ComponentType kMaxComponents = std::numeric_limits<ComponentType>::max();
using ComponentsSignature = std::bitset<kMaxComponents>;

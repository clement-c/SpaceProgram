#pragma once
#include "Entity.hpp"

class StaticEntity : public Entity
{
public:
    bool IsLoaded() const final { return true; }
};

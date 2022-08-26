#pragma once
#include <vector>

class Component;

class Entity
{
public:
    virtual bool IsLoaded() const = 0;

private:
    std::vector<Component*> m_components;
};

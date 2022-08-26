#pragma once
#include <stdint.h>

class Scene
{
public:
    bool AddEntity(uint32_t entityId, bool exclusiveToScene=false); // EntityLoader ? Points to a resource ID for lazy loading

    bool AllResourcesLoaded(float* outPerc) const;

private:

};

#pragma once
#include <stdint.h>

// Game resources vs scene resources

class ResourceManager
{
public:
    ResourceManager();

    uint32_t AddEntity();
    bool PreloadBuffer(); // preload a buffer from files or memory, return as address holder
};

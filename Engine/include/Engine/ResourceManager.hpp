#pragma once

class ResourceManager
{
public:
    bool PreloadBuffer(); // preload a buffer from files or memory, return as address holder

    template<typename EntityType>
    uint32_t LoadEntity(bool lazyLoad = false, int preloadLevel=-1);
};

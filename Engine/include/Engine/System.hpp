#pragma once
#include <stdint.h>
#include "Component.hpp"

/*
Systems own the memory specific to them.
A System can point to another system's memory map (components data) but then the target system cannot be shut down without shutting down the dependent system.

*/

struct System
{
    /**
     * @brief Reimplement if you want the system to be sometimes skipped
     * 
     * @return true 
     * @return false 
     */
    virtual bool IsDirty() const {
        return true;
    }

    template<typename T>
    T& GetComponent();
};

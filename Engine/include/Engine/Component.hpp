#pragma once

class Component
{
public:
    // bool IsLoaded() const; -> always loaded? Entity instance their own components

    // Pointers in the buffer of the system
    // TODO: replace with Buffer and custom memory manager
    void* DataStart() const;
    void* DataEnd() const;
};

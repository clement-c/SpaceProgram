#pragma once

class System
{
public:
    virtual bool Update(float);
    virtual const char* GetName() const;
};

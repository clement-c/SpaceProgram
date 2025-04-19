#pragma once
#include <vector>
#include <string>

struct Material
{

    enum class Type
    {
        kFlat = 0,
        kSolid = 2,
        kMatCap = 4,
        kPBR = 8,
        kDebugNormals = 16,
        kCustom = 24
    };

    Material(Type type);

private:
    Type m_type;
};

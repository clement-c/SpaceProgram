#pragma once
#include <vector>
#include <string>

struct Material
{
    enum class Type
    {
        kFlat = 0,
        kSolid = 2,
        kPBR = 8,
        kDebugNormals = 16
    };

    Material(std::string const &name, Type type);

private:
    std::string m_name;
    Type m_type;
};

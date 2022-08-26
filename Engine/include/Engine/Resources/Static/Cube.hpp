#include <vector>

#include "../../StaticEntity.hpp"

struct CubeTriangulated : public StaticEntity
{
    // TriangulatedMesh component - non dynamic topo by default
    static std::vector<float> vertices;
    static std::vector<float> textureCoord;
    static std::vector<uint32_t> triangles;

    // Transform component
};

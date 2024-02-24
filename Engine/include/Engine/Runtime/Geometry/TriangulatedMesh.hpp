#pragma once

#include <stdint.h>
#include <limits>
#include <vector>

#include "Engine/Core/Maths/Vector2.hpp"
#include "Engine/Core/Maths/Vector3.hpp"
#include "Engine/Core/Maths/Matrix44.hpp"

#include "Engine/Core/Logging.hpp"

struct Vertex
{
    Vector3 position;
    Vector3 normals;
    Vector2 uv;
};

struct TriangulatedMesh
{
    Matrix44 Transform;
    static size_t const NUM_FLOATS_PER_VTX = 8;

    TriangulatedMesh() : Transform{Matrix44::Identity()} {}
    TriangulatedMesh(Matrix44 const &transform) : Transform{transform} {}

    bool SetData(float verticesData[], uint32_t numVertices, int *trianglesData = nullptr, uint32_t numTriangles = 0)
    {
        // Set vertices data
        m_vertices.resize(numVertices * NUM_FLOATS_PER_VTX);
        memcpy(&(*m_vertices.begin()), verticesData, numVertices * 8 * sizeof(float));
        // Set faces data
        if (trianglesData)
        {
            // TODO: Implement face indices
            CC_LOG_ERROR("Passing triangles to build EBOs, but not implemented yet.");
            return false;
        }
        m_numVertices = numVertices;
        return true;
    }

    float const *RawData() const
    {
        return &(*m_vertices.begin());
    }

    uint32_t NumVertices() const { return m_numVertices; }

    void GetVertex(uint32_t index, Vertex *vtx)
    {
        if (index < m_numVertices)
            vtx = reinterpret_cast<Vertex *>(&(*(m_vertices.begin() + (index * NUM_FLOATS_PER_VTX))));
        else
            vtx = nullptr;
    }

private:
    std::vector<float> m_vertices; // positions, normals, texture_coords
    std::vector<uint32_t> m_triangles;
    uint32_t m_numVertices = 0;
    bool m_dirty = true;
};

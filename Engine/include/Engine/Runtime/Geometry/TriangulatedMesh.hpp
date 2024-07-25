#pragma once

#include <stdint.h>
#include <limits>
#include <vector>

#include "Engine/Core/Maths/Vector2.hpp"
#include "Engine/Core/Maths/Vector3.hpp"
#include "Engine/Core/Maths/Matrix44.hpp"
#include "Engine/Core/Maths/AABB.hpp"

#include "Engine/Core/Logging.hpp"

#include <iostream>

struct Vertex
{
    Vector3 Position;
    Vector3 Normals;
    Vector2 Uv;
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
        memcpy(&(*m_vertices.begin()), verticesData, numVertices * NUM_FLOATS_PER_VTX * sizeof(float));
        // Set faces data
        if (trianglesData)
        {
            // TODO: Implement face indices
            CC_LOG_ERROR("Passing triangles data to build EBOs, but not implemented yet.");
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

    void VertexAt(uint32_t index, Vertex *vtx)
    {
        if (index < m_numVertices)
            vtx = reinterpret_cast<Vertex *>(&(*(m_vertices.begin() + (index * NUM_FLOATS_PER_VTX))));
        else
            vtx = nullptr;
    }

    Vector4 GetPosition(uint32_t index) const
    {
        return Vector4(m_vertices[index * NUM_FLOATS_PER_VTX + 0], m_vertices[index * NUM_FLOATS_PER_VTX + 1], m_vertices[index * NUM_FLOATS_PER_VTX + 2]);
    }

    Vector2 GetUV(uint32_t index) const
    {
        return Vector2(m_vertices[index * NUM_FLOATS_PER_VTX + 3], m_vertices[index * NUM_FLOATS_PER_VTX + 4]);
    }

    Vector3 GetNormal(uint32_t index) const
    {
        return Vector3(m_vertices[index * NUM_FLOATS_PER_VTX + 5], m_vertices[index * NUM_FLOATS_PER_VTX + 6], m_vertices[index * NUM_FLOATS_PER_VTX + 7]);
    }

    Vector4 GetCenter() const
    {
        Vector3 center;
        Scalar step = 1.0f / m_numVertices;
        for(uint32_t i=0; i<m_numVertices; i++)
        {
            center.x += m_vertices[i * NUM_FLOATS_PER_VTX] * step;
            center.y += m_vertices[i * NUM_FLOATS_PER_VTX + 1] * step;
            center.z += m_vertices[i * NUM_FLOATS_PER_VTX + 2] * step;
        }
        return Vector4(center);
    }

    AABB GetBoundingBox() const noexcept
    {
        if(m_numVertices == 0)
        {
            return AABB();
        }
        else if(m_numVertices == 1) {
            Vector4 pos = GetPosition(0);
            return AABB(pos, pos);
        }

        AABB bb(GetPosition(0), GetPosition(1));
        for(uint32_t i=2; i<m_numVertices; i++)
            bb.Expand(Vector4(m_vertices[i * NUM_FLOATS_PER_VTX + 0], m_vertices[i * NUM_FLOATS_PER_VTX + 1], m_vertices[i * NUM_FLOATS_PER_VTX + 2]));
        return bb;
    }

private:
    std::vector<float> m_vertices; // positions, normals, texture_coords
    std::vector<uint32_t> m_triangles;
    uint32_t m_numVertices = 0;
    bool m_dirty = true;
};

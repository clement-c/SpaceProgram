#pragma once

#include "Engine/Runtime/Camera.hpp"
#include "Engine/Runtime/Geometry/TriangulatedMesh.hpp"

class RendererBackendI
{
public:
    virtual bool Initialize() { return true; }

    virtual uint32_t Upload(TriangulatedMesh const &) = 0;
    virtual bool Free(uint32_t) = 0;

    virtual bool SetMatrix(int32_t mesh_gpu_id, Matrix44 const &transform) = 0;
    virtual bool RenderAll() = 0;

    virtual bool UpdateCamera(Camera const &camera) noexcept
    {
        m_camera = camera;
        return true;
    }
    virtual void SetViewport(int w, int h)
    {
        m_width = w;
        m_height = h;
    }

protected:
    Camera m_camera;
    int m_width = 0;
    int m_height = 0;
};

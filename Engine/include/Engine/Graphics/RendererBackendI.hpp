#pragma once

// #include "Engine/Renderer.hpp"
#include "Engine/Runtime/Camera.hpp"
#include "Engine/Runtime/Geometry/TriangulatedMesh.hpp"
#include "Engine/Runtime/Texture.hpp"

struct Framebuffer;

class RendererBackendI
{
public:
    // virtual Renderer::API GetRendererAPI() const = 0;

    // Initialization and Cleanup
    virtual bool Initialize() = 0;
    virtual bool Shutdown() = 0;
    virtual ~RendererBackendI() = default;

    // virtual bool NewFramebuffer(Framebuffer *) = 0; // Uncommented the NewFramebuffer method

    // Resource Management
    virtual uint32_t UploadMesh(TriangulatedMesh const &) = 0;
    virtual uint32_t UploadTexture(Texture const &) = 0;
    virtual bool FreeMesh(uint32_t) = 0;
    // virtual bool FreeTexture(uint32_t) = 0;

    // Configuration
    // virtual bool SetRenderTarget(Window *) = 0;
    // virtual bool SetRenderTarget(Framebuffer *) = 0;
    // virtual bool SetRenderTarget(Texture *) = 0;

    // Scene rendering
    virtual bool UpdateMeshTransform(int32_t mesh_gpu_id, Matrix44 const &transform) = 0;
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

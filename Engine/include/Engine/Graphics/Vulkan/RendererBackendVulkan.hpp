#pragma once

#include "../RendererBackendI.hpp"

class RendererBackendVulkan : public RendererBackendI
{
public:
    //     RendererBackendVulkan() : RendererBackendI(), m_projMatrix{Matrix44::Identity()}, m_viewMatrix{Matrix44::Identity()} {
    //         CC_LOG_DEBUG("  RendererBackendVulkan::RendererBackendVulkan() done.\n");
    //     }

    virtual bool Initialize() final;

    virtual uint32_t UploadMesh(TriangulatedMesh const &) final;
    virtual bool UpdateMeshTransform(int32_t mesh_gpu_id, Matrix44 const &transform) final;
    virtual bool RenderAll() final;
    virtual bool FreeMesh(uint32_t) final;
    // virtual bool FreeTexture(uint32_t) final;

    virtual void SetViewport(int w, int h) final;

private:
};

#pragma once

#include "../RendererBackendI.hpp"
#include "GLVAO.hpp"
#include "GLProgram.hpp"

class RendererBackendOpenGL : public RendererBackendI
{
public:


    // virtual Renderer::API GetRendererAPI() const final
    // {
    //     return Renderer::API::kOpenGL45;
    // }

    virtual bool Initialize() final;
    virtual bool Shutdown() final;

    virtual uint32_t UploadMesh(TriangulatedMesh const &) final;
    virtual uint32_t UploadTexture(Texture const &) final;
    virtual bool FreeMesh(uint32_t) final;
    // virtual bool FreeTexture(uint32_t) final;

    virtual bool UpdateMeshTransform(int32_t mesh_gpu_id, Matrix44 const &transform) final;
    virtual bool RenderAll() final;

    virtual void SetViewport(int w, int h) final;

private:
    // TODO: update to better allocation for rapid allocation/deletion
    std::vector<GLVAO *> m_vaos;
    std::vector<Matrix44> m_modelMatrices;
    Matrix44 m_projMatrix, m_viewMatrix;
    // TODO: move to material management
    GLProgram m_program;
};

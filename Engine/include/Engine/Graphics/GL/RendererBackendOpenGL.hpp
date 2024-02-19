#pragma once

#include "../RendererBackendI.hpp"
#include "GLVAO.hpp"
#include "GLProgram.hpp"


class RendererBackendOpenGL : public RendererBackendI
{
public:
//     RendererBackendOpenGL() : RendererBackendI(), m_projMatrix{Matrix44::Identity()}, m_viewMatrix{Matrix44::Identity()} {
//         CC_LOG_DEBUG("  RendererBackendOpenGL::RendererBackendOpenGL() done.\n");
//     }

    virtual bool Initialize() final;

    virtual uint32_t Upload(TriangulatedMesh const &) final;
    virtual bool Free(uint32_t) final;
    virtual bool SetMatrix(int32_t mesh_gpu_id, Matrix44 const &transform) final;
    virtual bool RenderAll() final;

    virtual void SetViewport(int w, int h) final;

private:
    // TODO: update to better allocation for rapid allocation/deletion
    std::vector<GLVAO*> m_vaos;
    std::vector<Matrix44> m_modelMatrices;
    Matrix44 m_projMatrix, m_viewMatrix;
    // TODO: movbe to material management
    GLProgram m_program;
};

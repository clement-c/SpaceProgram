#pragma once

#include "Engine/Core/Logging.hpp"

#include "Engine/Graphics/GL/GLBuffer.hpp"
#include "Engine/Graphics/GL/GLProgram.hpp"
#include "Engine/Graphics/GL/RendererBackendOpenGL.hpp"

static const std::string SRC_VERTEX = R"vtx(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoords;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0f);
   TexCoords = aTexCoords;
   Normal = aNormal;
})vtx";

static const std::string SRC_FRAGMENT = R"frag(#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

void main()
{
   FragColor = vec4(Normal, 1.0f);
})frag";

bool RendererBackendOpenGL::Initialize()
{
    CC_LOG_DEBUG("  RendererBackendOpenGL::Initialize()\n");
    m_program = GLProgram(SRC_VERTEX, SRC_FRAGMENT);
    return m_program.Link();
}

uint32_t RendererBackendOpenGL::Upload(TriangulatedMesh const &mesh)
{
    CC_LOG_DEBUG("Uploading mesh using OpenGL backend...\n");
    GLBuffer mesh_buffer;
    mesh_buffer.SetData(
        mesh.RawData(),
        static_cast<size_t>(mesh.NumVertices()) * mesh.NUM_FLOATS_PER_VTX * sizeof(float),
        GLBuffer::Usage::StaticDraw);
    // TODO: vector is naive and pointer is a pain, all this will be improved with ResourceManager
    m_vaos.push_back(new GLVAO{
        mesh_buffer,
        {
            {0, {3, GL_FLOAT, false, (int)(8 * sizeof(float)), (void *)(0)}},                 // pos
            {1, {2, GL_FLOAT, false, (int)(8 * sizeof(float)), (void *)(3 * sizeof(float))}}, // texture_coord
            {2, {3, GL_FLOAT, true, (int)(8 * sizeof(float)), (void *)(5 * sizeof(float))}}   // normal
        }});
    m_modelMatrices.emplace_back();
    return m_vaos.size() - 1;
}

bool RendererBackendOpenGL::Free(uint32_t index)
{
    if (m_vaos.at(index))
    {
        delete m_vaos.at(index);
        return true;
    }
    return false;
}

bool RendererBackendOpenGL::SetMatrix(int32_t mesh_gpu_id, Matrix44 const &transform)
{
    m_modelMatrices.at(mesh_gpu_id) = transform;
    return true;
}

bool RendererBackendOpenGL::RenderAll()
{
    // TODO: PRIO 1 - Create options and move to windows
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //((sin(timeSec) * 0.5 + 0.5), 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // GLProgram should be set by renderer
    if (!m_program.Use())
    {
        CC_LOG_ERROR("Failed to use program during rendering.");
        return false;
    }

    // Set camera uniforms (projection/view)
    // TODO: dirty flag on projection matrix if the ratio is similar
    if (!m_program.SetUniform("projection", m_camera.GetProjectionMatrix(static_cast<float>(m_width) / static_cast<float>(m_height))) ||
        !m_program.SetUniform("view", m_camera.GetViewMatrix()))
    {
        CC_LOG_ERROR("Failed to set camera uniforms in shader.");
        return false;
    }

    // Set model uniform and launch draw per model
    for (uint32_t i = 0; i < m_modelMatrices.size(); i++)
    {
        if (!m_program.SetUniform("model", m_modelMatrices.at(i)) || !m_vaos.at(i)->Draw(GLVAO::DrawType::kTriangles))
        {
            CC_LOG_ERROR("failed to set model matrix uniform or render triangles");
            return false;
        }
    }

    return true;
}

void RendererBackendOpenGL::SetViewport(int w, int h)
{
    RendererBackendI::SetViewport(w, h);
    glViewport(0, 0, w, h);
}
#pragma once

// #include <iostream>

#include "Engine/Core/Logging.hpp"
#include "Engine/Core/Maths/Matrix33.hpp"

#include "Engine/Graphics/GL/GLBuffer.hpp"
#include "Engine/Graphics/GL/GLProgram.hpp"
#include "Engine/Graphics/GL/RendererBackendOpenGL.hpp"

static const std::string SRC_VERTEX = R"vtx(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    Normal = normalize(mat3(transpose(inverse(model))) * aNormal); // TODO: Move model matrix "homogenization" to render loop of engine to do it only once
    FragPos = vec3(model * vec4(aPos, 1.0f));

    gl_Position = projection * view * vec4(FragPos, 1.0f);
})vtx";

static const std::string SRC_FRAGMENT = R"frag(#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 defaultDirectional;

void main()
{
    vec3 col = min(max(dot(defaultDirectional, Normal), 0.0f), 1.0) * vec3(0.5f);
    FragColor = vec4(col, 1.0f);
})frag";

bool RendererBackendOpenGL::Initialize()
{
    CC_LOG_DEBUG("  RendererBackendOpenGL::Initialize()\n");
    m_program = GLProgram(SRC_VERTEX, SRC_FRAGMENT);
    return m_program.Link();
}

bool RendererBackendOpenGL::Shutdown()
{
    CC_LOG_DEBUG("  RendererBackendOpenGL::Shutdown()\n");
    for (auto vao : m_vaos)
    {
        if (vao)
            delete vao;
    }
    m_vaos.clear();
    return true;
}


uint32_t RendererBackendOpenGL::UploadMesh(TriangulatedMesh const &mesh)
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

uint32_t RendererBackendOpenGL::UploadTexture(Texture const &mesh)
{
    CC_LOG_DEBUG("Uploading texture using OpenGL backend...\n");
    return 0;
}

bool RendererBackendOpenGL::FreeMesh(uint32_t index)
{
    if (m_vaos.at(index))
    {
        delete m_vaos.at(index);
        m_vaos.at(index) = nullptr;
        return true;
    }
    return false;
}

bool RendererBackendOpenGL::UpdateMeshTransform(int32_t mesh_gpu_id, Matrix44 const &transform)
{
    m_modelMatrices.at(mesh_gpu_id) = transform;
    return true;
}

bool RendererBackendOpenGL::RenderAll()
{
    // TODO: PRIO 1 - Create options and move to windows (or render surface)
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //((sin(timeSec) * 0.5 + 0.5), 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // GLProgram should be set by renderer
    if (!m_program.Use())
    {
        CC_LOG_ERROR("Failed to use program during rendering.");
        return false;
    }

    auto view_matrix = m_camera.GetViewMatrix();
    Vector3 default_directional_light = Vector3(0.5, 0.707107, 0.5); // Points 45 degrees down and forward

    // Set camera uniforms (projection/view)
    // TODO: dirty flag on projection matrix, do not recompute if ratio is similar - maybe a projection matrix per RenderTarget
    if (!m_program.SetUniform("projection", m_camera.GetProjectionMatrix(static_cast<float>(m_width) / static_cast<float>(m_height))) ||
        !m_program.SetUniform("view", view_matrix))
    {
        CC_LOG_ERROR("Failed to set camera uniforms in shader.");
        return false;
    }
    m_program.SetUniform("defaultDirectional", default_directional_light); // TODO: Move to defaultMaterial

    // Set model uniform and launch draw per model
    for (uint32_t i = 0; i < m_modelMatrices.size(); i++)
    {
        if (!m_program.SetUniform("model", m_modelMatrices.at(i)) || !m_vaos.at(i)->Draw(GLVAO::DrawType::kTriangles))
        {
            CC_LOG_ERROR("failed to set model matrix uniform or render triangles");
            continue;
        }
    }
    return true;
}

void RendererBackendOpenGL::SetViewport(int w, int h)
{
    RendererBackendI::SetViewport(w, h);
    glViewport(0, 0, w, h);
}

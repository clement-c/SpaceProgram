#include <Engine/Core/Application.hpp>
#include <Engine/Core/Logging.hpp>

#include <Engine/Runtime/Camera.hpp>

#include <Engine/Graphics/GL/GLProgram.hpp>
#include <Engine/Graphics/GL/GLShader.hpp>

#include <Engine/Core/Maths/Matrix44.hpp>
#include <Engine/Graphics/GL/GLVAO.hpp>

#include "rsc/icosphere.hpp"

// TEMP:
#include <iostream>
#include <Engine/Core/Maths/MathsIO.hpp>

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

int main(int argc, char **argv)
{
    Application app(argc, argv);

    // Initialize engine with default systems
    auto &engine = app.GetEngine();
    if (!engine.Initialize())
    {
        CC_LOG_ERROR("Engine could not initialize.");
        return -1;
    }

    // Open a new window and center it
    uint32_t wind_id = app.NewWindow(1920, 1080, "02_GLSphere");
    app.GetWindowsManager().CenterWindow(wind_id);
    app.GetWindowsManager().MakeWindowCurrent(wind_id);


    glEnable(GL_DEPTH_TEST);


    // Create the OpenGL program
    GLProgram gl_program;
    gl_program.SetShader(GLShader::Type::kVertex, SRC_VERTEX);
    gl_program.SetShader(GLShader::Type::kFragment, SRC_FRAGMENT);
    if (!gl_program.Link()) // Compile and link, use - log errors if any
        return -1;

    // Initialise camera
    Camera camera;

    GLBuffer vbo(GLBuffer::Type::kArrayBuffer);
    vbo.SetData(Icosphere, sizeof(Icosphere), GL_STATIC_DRAW);

    // Register the buffers and their layouts in a VAO
    int padding = (int)(8 * sizeof(float));
    GLVAO vao_icosphere({
        { 0, {vbo, 3, GL_FLOAT, false, padding, (void*)(0)} }, // pos
        { 1, {vbo, 2, GL_FLOAT, false, padding, (void*)(3 * sizeof(float))} }, // texture_coord
        { 2, {vbo, 3, GL_FLOAT, true, padding, (void*)(5 * sizeof(float))} }  // normal
    });
    glViewport(0, 0, 1920, 1080);

    auto loop = [wind_id, &vao_icosphere, &camera, &engine, &gl_program](Application &app, double timeSec) -> int
    {
        // Matrix44 projection = Matrix44::projection(fov, screen_ratio, near_plane, far_plane);
        Matrix44 model = Matrix33::RotationY(static_cast<float>(timeSec));

        auto view = Matrix44::FromPosition(0.f, .0f, -9.0f);

        // app.GetWindowsManager().MakeWindowCurrent(0);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //((sin(timeSec) * 0.5 + 0.5), 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gl_program.Use();

        // Set mesh transform in the shader
        if (!gl_program.SetUniform("model", model) ||
            !gl_program.SetUniform("projection", camera.GetProjectionMatrix()) ||
            !gl_program.SetUniform("view", view)
            )
            return -1;

        vao_icosphere.Draw(GLVAO::DrawType::kTriangles);
        app.GetWindowsManager().SwapBuffers();

        return 0;
    };
    app.SetLoop(loop);

    return app.Run();
}

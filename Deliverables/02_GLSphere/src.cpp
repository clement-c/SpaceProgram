#include <Engine/Core/Application.hpp>
#include <Engine/Core/Window.hpp>
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

    int const WIN_WIDTH = 1920, WIN_HEIGHT = 1080;

    // Open a new window and center it
    uint32_t win_id = app.NewWindow(WIN_WIDTH, WIN_HEIGHT, "02_GLSphere");
    app.GetWindowsManager().CenterWindow(win_id);
    app.GetWindowsManager().MakeWindowCurrent(win_id);

    // Initialise camera

    Matrix44 model = Matrix44::Identity();
    auto loop = [&model](Application &app, double timeSec) -> int
    {
        model = Matrix33::RotationY(static_cast<float>(timeSec));
        return 0;
    };
    app.SetLoop(loop);

    // CUTSOM RENDERING IN THE MAIN WINDOW

    auto *window = app.GetWindowsManager().GetWindow(win_id);

    // Create the OpenGL program
    GLProgram gl_program;
    gl_program.SetShader(GLShader::Type::kVertex, SRC_VERTEX);
    gl_program.SetShader(GLShader::Type::kFragment, SRC_FRAGMENT);
    if (!gl_program.Link()) // Compile and link, use - log errors if any
        return -1;

    // Register the buffers and their layouts in a VAO
    GLBuffer vbo(GLBuffer::Type::kArrayBuffer);
    if (!vbo.SetData(Icosphere, sizeof(Icosphere), GL_STATIC_DRAW))
        return -1;
    GLVAO vao_icosphere(vbo, {
                                 {0, {3, GL_FLOAT, false, (int)(8 * sizeof(float)), (void *)(0)}},                 // pos
                                 {1, {2, GL_FLOAT, false, (int)(8 * sizeof(float)), (void *)(3 * sizeof(float))}}, // texture_coord
                                 {2, {3, GL_FLOAT, true, (int)(8 * sizeof(float)), (void *)(5 * sizeof(float))}}   // normal
                             });
    Camera camera;
    window->SetCustomRenderFunction(
        [&gl_program, &camera, &model, &vao_icosphere](Window const &window) -> bool
        {
            int width, height;

            auto view = Matrix44::FromPosition(0.f, .0f, -7.0f);

            glEnable(GL_DEPTH_TEST);

            if (window.GetSize(&width, &height))
            {
                glViewport(0, 0, width, height);
                camera.SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
            }
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //((sin(timeSec) * 0.5 + 0.5), 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            gl_program.Use();

            // Set mesh transform in the shader
            if (!gl_program.SetUniform("model", model) ||
                !gl_program.SetUniform("projection", camera.GetProjectionMatrix()) ||
                !gl_program.SetUniform("view", view))
                return false;

            vao_icosphere.Draw(GLVAO::DrawType::kTriangles);
            return true;
        });

    // auto renderLoop = [](Window& window, Engine& engine) -> bool

    return app.Run();
}

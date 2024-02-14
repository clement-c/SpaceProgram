#include <thread>

#include <Engine/Core/Application.hpp>
#include <Engine/Core/Logging.hpp>
#include <Engine/Scene.hpp>

#include <Engine/Graphics/GL/GLProgram.hpp>
#include <Engine/Graphics/GL/GLShader.hpp>

#include <Engine/Core/Math/Matrix44.hpp>

// cube vertices
static float gVertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // pos, uv
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

int main(int argc, char **argv)
{

    Application app;

    auto &engine = app.GetEngine();
    if (!engine.Initialize())
    {
        CC_LOG_ERROR("Engine could not initialize.");
        return -1;
    }

    uint32_t wind_id = app.NewWindow(1920, 1080, "02_GLSphere");
    app.GetWindowsManager().CenterWindow(wind_id);
    app.GetWindowsManager().MakeWindowCurrent(wind_id);

    GLProgram gl_program;

    gl_program.SetShader(GLShader::Type::kVertex,
                         R"vtx(#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0f); 
})vtx");

    gl_program.SetShader(GLShader::Type::kFragment,
                         R"frag(#version 330 core
out vec4 FragColor;

void main()
{
   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
})frag");

    if (!gl_program.Use())
        return -1; // GLProgram, will output its own error

    Matrix44 view{
        1.f, .0f, .0f, .0f,
        0.f, 1.f, .0f, .0f,
        0.f, .0f, 1.f, .0f,
        0.f, .0f, -3.f, 1.f};

    auto loop = [wind_id, &engine, &gl_program](Application &app, double timeSec) -> int
    {
        // Matrix44 projection = Matrix44::projection(fov, screen_ratio, near_plane, far_plane);
        Matrix44 model = Matrix44::Identity();

        // Set mesh transform in the shader
        if (!gl_program.SetUniform("model", model))
            return -1;

        // Get window surface
        // srf = app.GetWindowsManager().GetCurrentWindowSurface() // updated with resize

        // Update camera

        // Set projection and view matrices from Camera and render surface

        // Render on main window

        // renderer.Render(&scene, cameraId, srf);

        // windows to be refreshed outside loop
        return 0;
    };
    app.SetLoop(loop);

    return app.Run();
}

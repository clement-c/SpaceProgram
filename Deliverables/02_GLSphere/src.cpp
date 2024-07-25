#include <Engine/Core/Application.hpp>
#include <Engine/Core/Window.hpp>
#include <Engine/Core/Logging.hpp>
#include <Engine/Core/Maths/Matrix44.hpp>

#include <Engine/Runtime/Camera.hpp>
#include <Engine/Runtime/Geometry/TriangulatedMesh.hpp>

// Mesh to draw
#include "rsc/icosphere.hpp"

int main(int argc, char **argv)
{
    int const WIN_WIDTH = 1280, WIN_HEIGHT = 720;

    Application app(argc, argv);

    // Initialize engine with default systems
    auto &engine = app.GetEngine();
    if (!engine.Initialize())
    {
        CC_LOG_ERROR("Engine could not initialize.");
        return -1;
    }

    // Open a new window and center it
    Window *const main_window = app.NewWindow(WIN_WIDTH, WIN_HEIGHT, "Deliverable 02 - GLSphere");

    // Get the renderer, 1 renderer per window for now - need to check context sharing and glad initialization when mulptilpe windows
    auto &renderer = main_window->GetRenderer();

    // Set a static camera
    Camera camera;
    Matrix44 viewMatrix = Matrix44::FromPosition(0.f, .0f, -7.0f);
    camera.SetViewMatrix(viewMatrix);
    renderer.UpdateCamera(camera);

    // Upload mesh to the GPU
    int planet_gpu_id = -1;
    int moon_gpu_id = -1;
    {
        // Create and upload mesh
        TriangulatedMesh sphere;
        sphere.SetData(Icosphere, sizeof(Icosphere) / 8 / sizeof(float)); // array of floats, 8 per face-vertex (p:xyz, n:xyz, t:uv)
        planet_gpu_id = renderer.Upload(sphere);
        moon_gpu_id = renderer.Upload(sphere);
    }

    // Moon is scaled 0.2, translated 3.5
    Matrix44 moon_base_transf = {
        .2f, 0.f, 0.f, 0.f,
        0.f, .2f, 0.f, 0.f,
        0.f, 0.f, .2f, 0.f,
        0.f, 0.f, 3.5f, 1.f};

    float rotate = 0;

    // Loop
    auto loop = [&renderer, &moon_base_transf, &main_window, &rotate, &camera, planet_gpu_id, moon_gpu_id](Application &app, double timeSec) -> int
    {
        Matrix44 rotation = Matrix44(Matrix33::RotationY(static_cast<float>(timeSec * 0.5)));

        // Keyboard events
        //   Quit on Q
        if (main_window->IsKeyPressed(KeyboardEvent::Key::KeyQ))
            return 1;
        //   Orbit camera with left/right keys
        if (main_window->IsKeyPressed(KeyboardEvent::Key::KeyLeft))
            rotate += 0.02f;
        else if (main_window->IsKeyPressed(KeyboardEvent::Key::KeyRight))
            rotate -= 0.02f;

        auto view_matrix = Matrix44(Matrix33::RotationY(rotate)) * Matrix44::FromPosition(0.f, .0f, -7.0f); // Checked, this is correct
        camera.SetViewMatrix(view_matrix);

        renderer.UpdateCamera(camera);

        // Transform a mesh already uploaded to GPU using its ID in the renderer
        renderer.TransformEntity(planet_gpu_id, rotation);
        renderer.TransformEntity(moon_gpu_id, moon_base_transf * rotation);
        return 0;
    };
    app.SetLoop(loop);

    return app.Run();
}

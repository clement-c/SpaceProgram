#include <Engine/Core/Application.hpp>
#include <Engine/Core/Window.hpp>
#include <Engine/Core/Logging.hpp>
#include <Engine/Core/Maths/Matrix44.hpp>

#include <Engine/Runtime/Camera.hpp>
#include <Engine/Runtime/Geometry/TriangulatedMesh.hpp>

// Mesh to draw
#include "rsc/icosphere.hpp"

#include <iostream>

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
    camera.SetViewMatrix(Matrix44::FromPosition(0.f, .0f, -7.0f));
    renderer.UpdateCamera(camera);

    // Upload mesh to the GPU
    int mesh_gpu_id = -1;
    {
        // Create and upload mesh
        TriangulatedMesh mesh;
        mesh.SetData(Icosphere, 960u);
        mesh_gpu_id = renderer.Upload(mesh);
    }

    // Loop
    auto loop = [&renderer, mesh_gpu_id](Application &app, double timeSec) -> int
    {
        Matrix44 rotation = Matrix44(Matrix33::RotationY(static_cast<float>(timeSec * 0.5)));
        // Transform a mesh already uploaded to GPU using its ID in the renderer
        renderer.TransformEntity(mesh_gpu_id, rotation);
        return 0;
    };

    app.SetLoop(loop);
    return app.Run();
}

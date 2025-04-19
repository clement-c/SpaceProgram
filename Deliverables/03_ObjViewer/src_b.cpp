#include <Engine/Core/Application.hpp>
#include <Engine/Core/Window.hpp>
#include <Engine/Core/Logging.hpp>
#include <Engine/Core/System/Path.hpp>
#include <Engine/Scene.hpp>

#include <Engine/Runtime/Camera.hpp>
#include <Engine/Core/Maths/MathsIO.hpp>

#include <Engine/Core/System/Args.hpp>

#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"


bool LoadRsc(char const *path, std::vector<TriangulatedMesh> &outMeshes)
{
    bool status = false;
    return status;
}

int main(int argc, char **argv)
{
    int const WIN_WIDTH = 1920 * 0.9, WIN_HEIGHT = 1080 * 0.9;

    Application app(argc, argv);

    // Initialize engine with default systems
    auto &engine = app.GetEngine();
    if (!engine.Initialize())
    {
        CC_LOG_ERROR("Engine could not initialize.");
        return -1;
    }

    // Open a new window and center it
    Window *const main_window = app.NewWindow(WIN_WIDTH, WIN_HEIGHT, "Deliverable 03 - ObjViewer");

    ResourceManager &resource_manager = engine.GetResourceManager();

    // Queue assets for loading
    Loader &loader = resource_manager.NewLoader();
    AssetRef sun_asset = loader.Enqueue("rsc/sun.entity");

    Scene scene;
    scene.AddEntity(sun_asset);

    // Load model as entity
    std::vector<TriangulatedMesh> model;
    LoadRsc("rsc03/scene.entity", model);

    // UploadMesh mesh
    auto &renderer = main_window->GetRenderer();
    int32_t model_id = renderer.UploadMesh(model[0]);

    // Set Camera
    Camera camera;
    Vector4 mesh_center = model[0].GetCenter();
    Matrix44 cam_matrix = Matrix44::FromPosition(0.0, mesh_center.y, 7.0);
    camera.SetMatrix(cam_matrix);
    renderer.UpdateCamera(camera);

    auto loop = [&camera, &renderer, &cam_matrix, model_id](Application &app, double timeSec) -> int
    {
        Matrix44 rotation = Matrix44(Matrix33::RotationY(static_cast<float>(timeSec * -0.5)));
        renderer.TransformItem(model_id, rotation);
        return 0;
    };
    app.SetLoop(loop);

    return app.Run();
}

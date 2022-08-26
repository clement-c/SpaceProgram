#include <thread>

#include <Engine/Core/Application.hpp>
#include <Engine/Core/Logging.hpp>
// #include <Engine/Engine/Scene.hpp>

int main(int argc, char** argv)
{

    Application app;

    app.NewWindow(1920, 1080, "02_GLSphere");
    app.GetWindowsManager().CenterWindow(0);

    if(!app.InitializeEngine())
    {
        CC_LOG_ERROR("Engine could not initialize.");
        return -1;
    }
    auto& layer3d = app.GetEngine().AddRenderLayer(0);

    /*
    Scene scene;
    scene.AddStaticEntity(staticSphere); // vs scene.LoadEntity()
    scene.AddStaticEntity(camera);
    scene.SetCamera(camera);
    camera.LookAt(staticSphere, staticSphere.GetRadius() * 4.0f, staticSphere.GetRadius() * 1.5f); // target, distance, elevation
    layer.SetScene(scene, camera);
    */

    auto loop = [](Application& app, double time) -> int {
        // staticSphere.SetRotate(0, time, 0);
        return 1;
    };
    app.SetLoop(loop);

    app.Run();

    return 0;
}

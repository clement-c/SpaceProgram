#include <Engine/Core/Application.hpp>
#include <Engine/Core/Window.hpp>
#include <Engine/Core/Logging.hpp>
#include <Engine/Scene.hpp>

#include <Engine/Runtime/Camera.hpp>

int main(int argc, char **argv)
{
    int const WIN_WIDTH = 1920, WIN_HEIGHT = 1080;

    Application app(argc, argv);

    // Initialize engine with default systems
    auto &engine = app.GetEngine();
    if (!engine.Initialize())
    {
        CC_LOG_ERROR("Engine could not initialize.");
        return -1;
    }

    // Open a new window and center it
    Window *const main_window = app.NewWindow(WIN_WIDTH, WIN_HEIGHT, "Deliverable 30 - Resources");
    auto &renderer = main_window->GetRenderer();

    auto &resource_manager = engine.GetResourceManager();

    // Queue assets for loading
    auto& loader = resource_manager.NewLoader();

    AssetRef sun_asset = loader.Enqueue("rsc/sun.entity");
    loader.Enqueue("rsc/mercury.entity");
    loader.Enqueue("rsc/venus.entity");
    loader.Enqueue("rsc/earth.entity");
    loader.Enqueue("rsc/mars.entity");
    loader.Enqueue("rsc/jupiter.entity");
    loader.Enqueue("rsc/saturn.entity");
    loader.Enqueue("rsc/uranus.entity");
    loader.Enqueue("rsc/neptune.entity");
    // Allow loader.Enqueue("rsc/*.entity"); ? More likely have an index

    // Handle loader events
    loader.OnLoadProgress([](int bytes_loaded, int bytes_total)
                          { CC_LOG_DEBUG("Loading resources ({}/{})...\n", bytes_loaded, bytes_total); });
    loader.OnLoadError([](AssetRef failed_asset /*, report*/)
                       {
                           return false; // return true to stop further loading
                       });

    // Can build the scene already with the refs
    Scene scene;
    scene.AddEntity(sun_asset);
    scene.AddEntity("rsc/venus.entity");

    loader.OnLoadComplete([&engine, &scene]()
                          { engine.SetScene(scene); });
    // can (should) be launched in another thread, blocking
    loader.Load();

    return app.Run();
}
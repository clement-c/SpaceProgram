# 03_Resources deliverable

## Draft code

```cpp
engine = app.GetEngine();
if(!engine.Initialize()) return -1;

resource_manager = engine.GetResourceManager();

auto loader = resource_manager.NewLoader();

AssetRef sun_asset = loader.Enqueue("rsc/sun.entity");
// AssetRef ref
// ref.uuid
// ref.path
// ref.status
// ref.type
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
loader.OnLoadProgress([](int bytes_loaded, int bytes_total){
    CC_DEBUG_LOG("Loading resources ({}/{})\n", bytes_loaded, bytes_total);
});
loader.OnLoadError([](AssetRef failed_asset /*, report*/){
    return false; // return true to stop further loading
});

// Can build the scene already with the refs
Scene scene;
scene.AddEntity(sun_asset);
scene.AddEntity("rsc/venus.entity");

loader.OnLoadComplete([&engine, &scene](){
    engine.SetScene(scene);
});
// can (should) be launched in another thread, blocking
loader.Load();

// Scene will be launched at the end of load
```

## Entities

```json

```

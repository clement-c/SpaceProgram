#include <gtest/gtest.h>

#include <Engine/Engine.hpp>
#include <Engine/ResourceManager.hpp>
#include <Engine/Scene.hpp>

#include <fstream>

// Helper to create a temporary test asset file
class TestAssetFile {
public:
    TestAssetFile(const std::string& path, const std::string& content) : m_path(path) {
        std::ofstream file(path);
        file << content;
        file.close();
    }
    
    ~TestAssetFile() {
        std::remove(m_path.c_str());
    }
    
private:
    std::string m_path;
};

/* ================== ResourceManager Tests ================== */

TEST(ResourceManager, Loader_EnqueueAsset)
{
    Loader loader;
    
    // Create a temporary test file
    TestAssetFile testFile("test_asset.entity", "{\"test\": \"data\"}");
    
    AssetRef asset = loader.Enqueue("test_asset.entity");
    
    EXPECT_EQ(asset.path, "test_asset.entity");
    EXPECT_EQ(asset.type, AssetType::Entity);
    EXPECT_EQ(asset.status, AssetStatus::Pending);
    EXPECT_GT(asset.uuid, 0);
}

TEST(ResourceManager, Loader_EnqueueMultipleAssets)
{
    Loader loader;
    
    // Create temporary test files
    TestAssetFile file1("asset1.entity", "{}");
    TestAssetFile file2("asset2.entity", "{}");
    TestAssetFile file3("asset3.entity", "{}");
    
    AssetRef asset1 = loader.Enqueue("asset1.entity");
    AssetRef asset2 = loader.Enqueue("asset2.entity");
    AssetRef asset3 = loader.Enqueue("asset3.entity");
    
    EXPECT_NE(asset1.uuid, asset2.uuid);
    EXPECT_NE(asset2.uuid, asset3.uuid);
    EXPECT_NE(asset1.uuid, asset3.uuid);
}

TEST(ResourceManager, Loader_EnqueueDuplicateAsset)
{
    Loader loader;
    
    TestAssetFile testFile("duplicate.entity", "{}");
    
    AssetRef asset1 = loader.Enqueue("duplicate.entity");
    AssetRef asset2 = loader.Enqueue("duplicate.entity");
    
    // Should return the same asset reference
    EXPECT_EQ(asset1.uuid, asset2.uuid);
    EXPECT_EQ(asset1.path, asset2.path);
}

TEST(ResourceManager, Loader_DetermineAssetType)
{
    Loader loader;
    
    TestAssetFile entity("test.entity", "{}");
    TestAssetFile model("test.obj", "");
    TestAssetFile texture("test.png", "");
    
    AssetRef entityRef = loader.Enqueue("test.entity");
    AssetRef modelRef = loader.Enqueue("test.obj");
    AssetRef textureRef = loader.Enqueue("test.png");
    
    EXPECT_EQ(entityRef.type, AssetType::Entity);
    EXPECT_EQ(modelRef.type, AssetType::Model);
    EXPECT_EQ(textureRef.type, AssetType::Texture);
}

TEST(ResourceManager, Loader_LoadSingleAsset)
{
    Loader loader;
    
    TestAssetFile testFile("loadable.entity", "{}");
    
    AssetRef asset = loader.Enqueue("loadable.entity");
    bool success = loader.Load(asset);
    
    EXPECT_TRUE(success);
    EXPECT_EQ(asset.status, AssetStatus::Loaded);
}

TEST(ResourceManager, Loader_LoadNonExistentAsset)
{
    Loader loader;
    
    AssetRef asset = loader.Enqueue("nonexistent.entity");
    bool success = loader.Load(asset);
    
    EXPECT_FALSE(success);
    EXPECT_EQ(asset.status, AssetStatus::Failed);
}

TEST(ResourceManager, Loader_LoadAllAssets)
{
    Loader loader;
    
    TestAssetFile file1("load1.entity", "{}");
    TestAssetFile file2("load2.entity", "{}");
    TestAssetFile file3("load3.entity", "{}");
    
    loader.Enqueue("load1.entity");
    loader.Enqueue("load2.entity");
    loader.Enqueue("load3.entity");
    
    bool success = loader.LoadAll();
    
    EXPECT_TRUE(success);
}

TEST(ResourceManager, Loader_ProgressCallback)
{
    Loader loader;
    
    TestAssetFile file1("prog1.entity", "{}");
    TestAssetFile file2("prog2.entity", "{}");
    
    loader.Enqueue("prog1.entity");
    loader.Enqueue("prog2.entity");
    
    int progressCalls = 0;
    int lastLoaded = 0;
    int lastTotal = 0;
    
    loader.OnLoadProgress([&](int loaded, int total) {
        progressCalls++;
        lastLoaded = loaded;
        lastTotal = total;
    });
    
    loader.LoadAll();
    
    EXPECT_GT(progressCalls, 0);
    EXPECT_EQ(lastLoaded, 2);
    EXPECT_EQ(lastTotal, 2);
}

TEST(ResourceManager, Loader_CompleteCallback)
{
    Loader loader;
    
    TestAssetFile file1("comp1.entity", "{}");
    
    loader.Enqueue("comp1.entity");
    
    bool completeCalled = false;
    
    loader.OnLoadComplete([&]() {
        completeCalled = true;
    });
    
    loader.LoadAll();
    
    EXPECT_TRUE(completeCalled);
}

TEST(ResourceManager, Loader_ErrorCallback)
{
    Loader loader;
    
    loader.Enqueue("missing.entity");
    
    bool errorCalled = false;
    
    loader.OnLoadError([&](AssetRef asset) {
        errorCalled = true;
        return false; // Don't stop loading
    });
    
    loader.LoadAll();
    
    EXPECT_TRUE(errorCalled);
}

TEST(ResourceManager, ResourceManager_NewLoader)
{
    ResourceManager manager;
    
    Loader& loader1 = manager.NewLoader();
    Loader& loader2 = manager.NewLoader();
    
    // Should get different loaders
    EXPECT_NE(&loader1, &loader2);
}

TEST(ResourceManager, ResourceManager_MainLoader)
{
    ResourceManager manager;
    
    Loader& mainLoader1 = manager.MainLoader();
    Loader& mainLoader2 = manager.MainLoader();
    
    // Should get the same main loader
    EXPECT_EQ(&mainLoader1, &mainLoader2);
}

/* ================== Scene Tests ================== */

TEST(Scene, AddEntity_WithAssetRef)
{
    Scene scene;
    
    AssetRef asset(123, "test.entity", AssetType::Entity);
    Entity::EntityId id = scene.AddEntity(asset);
    
    EXPECT_GE(id, 0);
}

TEST(Scene, AddEntity_WithPath)
{
    Scene scene;
    
    Entity::EntityId id = scene.AddEntity("test.entity");
    
    EXPECT_GE(id, 0);
}

TEST(Scene, Activate_Deferred)
{
    Scene scene;
    
    scene.AddEntity("entity1.entity");
    scene.AddEntity("entity2.entity");
    
    bool success = scene.Activate(true);
    
    EXPECT_TRUE(success);
}

TEST(Scene, Activate_Blocking)
{
    Scene scene;
    
    scene.AddEntity("entity1.entity");
    scene.AddEntity("entity2.entity");
    
    bool success = scene.Activate(false);
    
    EXPECT_TRUE(success);
}

/* ================== Engine Tests ================== */

TEST(Engine, GetResourceManager)
{
    Engine engine;
    
    ResourceManager& manager1 = engine.GetResourceManager();
    ResourceManager& manager2 = engine.GetResourceManager();
    
    // Should get the same resource manager instance
    EXPECT_EQ(&manager1, &manager2);
}

TEST(Engine, SetScene)
{
    Engine engine;
    engine.Initialize();
    
    Scene scene;
    scene.AddEntity("test.entity");
    
    // Should not crash
    engine.SetScene(scene);
}

# Resource Loading System Implementation

## Overview

This implementation provides a complete ECS-based resource loading system for the SpaceProgram engine. The system enables loading and managing game resources such as models, textures, materials, and entity definitions.

## Architecture

### Core Components

1. **AssetRef**: Reference to a game asset
   - `uuid`: Unique identifier for the asset
   - `path`: File path to the asset
   - `status`: Current loading status (Pending, Loading, Loaded, Failed)
   - `type`: Asset type (Entity, Model, Texture, Material, Shader, Audio)
   - `data`: Pointer to loaded resource data

2. **Loader**: Handles queuing and loading of assets
   - Maintains a manifest of queued assets
   - Supports asynchronous loading with callbacks
   - Provides progress tracking and error handling

3. **ResourceManager**: Central manager for all resource loaders
   - Provides main loader for application-wide resources
   - Supports creating additional loaders for scene-specific resources

### Asset Types

The system supports the following asset types:

- **Entity** (.entity): JSON-based entity definitions with components
- **Model** (.obj, .fbx, .gltf, .glb): 3D mesh data
- **Texture** (.png, .jpg, .jpeg, .bmp, .tga): Image data
- **Material** (.mat, .material): Material definitions
- **Shader** (.glsl, .vert, .frag, .shader): Shader programs
- **Audio** (.wav, .mp3, .ogg): Audio files

## API Usage

### Basic Loading

```cpp
// Initialize engine
Engine engine;
engine.Initialize();

// Get resource manager
auto& resource_manager = engine.GetResourceManager();

// Create a loader
auto& loader = resource_manager.NewLoader();

// Queue assets for loading
AssetRef sun = loader.Enqueue("rsc/sun.entity");
loader.Enqueue("rsc/earth.entity");
loader.Enqueue("rsc/moon.entity");

// Load all queued assets
loader.LoadAll();
```

### With Callbacks

```cpp
// Progress callback
loader.OnLoadProgress([](int loaded, int total) {
    printf("Loading: %d/%d\n", loaded, total);
});

// Error callback
loader.OnLoadError([](AssetRef failed_asset) {
    printf("Failed to load: %s\n", failed_asset.path.c_str());
    return false; // continue loading other assets
});

// Complete callback
loader.OnLoadComplete([]() {
    printf("All assets loaded!\n");
});

// Start loading
loader.LoadAll();
```

### Scene Integration

```cpp
// Create a scene
Scene scene;

// Add entities using asset references
scene.AddEntity(sun);
scene.AddEntity("rsc/venus.entity");

// Activate scene (blocking)
scene.Activate(false);

// Or activate asynchronously
scene.Activate(true);

// Set as active scene in engine
engine.SetScene(scene);
```

## Entity File Format

Entity files use JSON format to define entity components:

```json
{
  "name": "Sun",
  "components": {
    "transform": {
      "position": [0.0, 0.0, 0.0],
      "rotation": [0.0, 0.0, 0.0],
      "scale": [2.0, 2.0, 2.0]
    },
    "mesh": {
      "type": "sphere",
      "radius": 1.0
    },
    "material": {
      "type": "solid",
      "color": [1.0, 0.9, 0.2, 1.0],
      "emissive": true
    },
    "light": {
      "type": "point",
      "intensity": 1.0,
      "color": [1.0, 0.9, 0.8]
    }
  }
}
```

## Implementation Details

### Loader Class

The `Loader` class provides:

- **Enqueue(path)**: Queue an asset for loading
  - Automatically detects asset type from file extension
  - Returns AssetRef for tracking
  - Prevents duplicate queuing

- **LoadAll()**: Load all queued assets
  - Iterates through manifest
  - Calls progress callbacks
  - Handles errors with error callbacks
  - Calls complete callback when done

- **FindAsset(uuid/path)**: Look up loaded assets
  - Find by UUID for fast lookup
  - Find by path for string-based queries

### Asset Loading Flow

1. **Queue Phase**: Assets are added to loader manifest via `Enqueue()`
2. **Load Phase**: `LoadAll()` processes manifest
   - Sets status to Loading
   - Calls `LoadAsset()` for each asset
   - Updates status to Loaded or Failed
   - Triggers callbacks
3. **Access Phase**: Assets can be retrieved via `FindAsset()`

### Scene Entity Management

The `Scene` class now supports:

- **AddEntity(AssetRef)**: Add entity from asset reference
- **AddEntity(path)**: Add entity from file path
- **Activate(deferred)**: Load and activate entities
  - `deferred=false`: Blocks until all entities loaded
  - `deferred=true`: Returns immediately, loads in background

## Testing

Comprehensive unit tests cover:

- Asset enqueueing and duplicate handling
- Asset type detection
- Single and batch loading
- Progress, error, and complete callbacks
- Scene integration
- Engine integration

Run tests with:
```bash
./test_resource_manager
```

## Future Enhancements

Planned improvements:

1. **Full Asset Parsing**
   - Implement JSON parsing for entity files
   - Add OBJ/FBX model loading
   - Add image texture loading

2. **Memory Management**
   - Reference counting for shared assets
   - Automatic unloading of unused assets
   - Asset pooling and caching

3. **Streaming**
   - Background thread loading
   - Progressive loading for large assets
   - Network-based asset loading

4. **Hot Reloading**
   - File watching for asset changes
   - Automatic reload on modification
   - Live updates in editor mode

## Example: Deliverable 04

See `Deliverables/04_Resources/src.cpp` for a complete example demonstrating:
- Engine initialization
- Resource loading with callbacks
- Scene creation with loaded entities
- Integration with rendering system

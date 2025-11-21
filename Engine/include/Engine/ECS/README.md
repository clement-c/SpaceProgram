# ECS (Entity-Component-System) Framework

A high-performance, header-only Entity-Component-System implementation for the SpaceProgram engine.

## Features

- **Efficient Component Storage**: Uses packed arrays with Structure of Arrays (SoA) layout for cache-friendly iteration
- **Entity Recycling**: Reuses entity IDs with version numbers to prevent dangling references
- **Signature-based Filtering**: Systems automatically track entities with matching component signatures
- **Serial Execution**: Systems run serially in the main thread (designed for future parallel execution)
- **ImGui Integration**: Built-in debugger for inspecting and modifying entities and components at runtime
- **Header-Only**: No compilation required, just include `Engine/ECS/ECS.hpp`

## Architecture

### Core Components

1. **Entity**: Simple integer ID representing a game object
2. **Component**: Plain data structures (POD) holding entity state
3. **System**: Logic that operates on entities with specific component combinations
4. **World**: Main coordinator managing entities, components, and systems

### Memory Layout

Components are stored using a **packed array** approach for optimal cache performance:
- Each component type has its own contiguous array
- Dense packing eliminates holes when entities are destroyed
- Lookup uses hash maps for O(1) access time

## Quick Start

### 1. Include the ECS Header

```cpp
#include <Engine/ECS/ECS.hpp>
#include <Engine/ECS/Components.hpp>  // For built-in components
```

### 2. Create a World

```cpp
using namespace Engine::ECS;

World world;
```

### 3. Define Components

Components are plain structs:

```cpp
struct Position {
    float x, y, z;
    Position(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

struct Velocity {
    float x, y, z;
    Velocity(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
```

### 4. Register Components

```cpp
world.RegisterComponent<Position>();
world.RegisterComponent<Velocity>();
```

### 5. Create a System

Systems inherit from `System` and implement `Update()`:

```cpp
class PhysicsSystem : public System {
public:
    void Update(float deltaTime) override {
        for (Entity entity : m_entities) {
            auto& pos = m_world->GetComponent<Position>(entity);
            auto& vel = m_world->GetComponent<Velocity>(entity);
            
            pos.x += vel.x * deltaTime;
            pos.y += vel.y * deltaTime;
            pos.z += vel.z * deltaTime;
        }
    }
    
    const char* GetName() const override {
        return "PhysicsSystem";
    }
    
    void SetWorld(World* world) { m_world = world; }
    
private:
    World* m_world = nullptr;
};
```

### 6. Register and Configure Systems

```cpp
auto physicsSystem = world.RegisterSystem<PhysicsSystem>();
physicsSystem->SetWorld(&world);

// Define which components this system requires
Signature signature;
signature.set(world.GetComponentType<Position>());
signature.set(world.GetComponentType<Velocity>());
world.SetSystemSignature<PhysicsSystem>(signature);
```

### 7. Create Entities and Add Components

```cpp
Entity entity = world.CreateEntity();
world.AddComponent(entity, Position{0.0f, 0.0f, 0.0f});
world.AddComponent(entity, Velocity{1.0f, 0.5f, 0.0f});
```

### 8. Run the Game Loop

```cpp
world.InitSystems();

while (running) {
    float deltaTime = CalculateDeltaTime();
    world.UpdateSystems(deltaTime);
}

world.ShutdownSystems();
```

## ImGui Integration

The ECS includes a built-in debugger for runtime inspection:

```cpp
#include <Engine/ECS/ECSDebugger.hpp>

ECSDebugger debugger(world);
debugger.TrackEntity(entity, "Player");

// In your render loop:
debugger.Render();
```

The debugger provides:
- **Entity Browser**: View all tracked entities
- **Component Inspector**: View and edit component values in real-time
- **System Statistics**: Monitor system execution and entity counts

## Built-in Components

The framework includes several pre-defined components in `Engine/ECS/Components.hpp`:

- **Position**: 3D position (x, y, z)
- **Velocity**: 3D velocity (x, y, z)
- **Rotation**: Euler angles (pitch, yaw, roll)
- **Name**: String identifier (64 chars)

## Examples

### Console Example

A simple console-based example demonstrating ECS basics:

```bash
./build/Engine/ECSExample
```

### ImGui Demo

Interactive demo with visual debugging:

```bash
./build/Engine/ECSDemo
```

This demo shows:
- Real-time entity inspection
- Component value editing
- System execution visualization

## Testing

Run the ECS unit tests:

```bash
cd build/Tests
./test_ecs
```

Tests cover:
- Entity creation and destruction
- Component management
- System execution
- Signature-based filtering
- Entity recycling

## Performance Considerations

### Cache-Friendly Design

Components are stored in packed arrays, ensuring:
- Sequential memory access during iteration
- Minimal cache misses
- Optimal SIMD opportunities

### Entity Recycling

Destroyed entities are recycled to:
- Avoid memory fragmentation
- Reuse allocated IDs
- Maintain stable iteration performance

### System Ordering

Systems execute in registration order. For optimal performance:
- Order systems to minimize cache misses
- Group related systems together
- Consider data dependencies

## Future Enhancements

The ECS is designed with future parallelization in mind:

1. **Dependency Graph**: Track system dependencies for parallel scheduling
2. **Job System Integration**: Use libraries like Taskflow for multi-threading
3. **Archetype Storage**: Consider archetype-based storage for even better performance
4. **Component Pools**: Pre-allocate component memory for predictable allocation

## API Reference

### World

- `Entity CreateEntity()` - Create a new entity
- `void DestroyEntity(Entity)` - Destroy an entity
- `void RegisterComponent<T>()` - Register a component type
- `void AddComponent<T>(Entity, T)` - Add component to entity
- `void RemoveComponent<T>(Entity)` - Remove component from entity
- `T& GetComponent<T>(Entity)` - Get component reference
- `bool HasComponent<T>(Entity)` - Check if entity has component
- `std::shared_ptr<T> RegisterSystem<T>()` - Register a system
- `void SetSystemSignature<T>(Signature)` - Set system's required components
- `void InitSystems()` - Initialize all systems
- `void UpdateSystems(float)` - Update all systems
- `void ShutdownSystems()` - Shutdown all systems

### System

- `virtual void Init()` - Called once during initialization
- `virtual void Update(float)` - Called every frame
- `virtual void Shutdown()` - Called during cleanup
- `virtual const char* GetName()` - Return system name for debugging
- `std::set<Entity> m_entities` - Set of entities matching this system's signature

## License

Part of the SpaceProgram project.

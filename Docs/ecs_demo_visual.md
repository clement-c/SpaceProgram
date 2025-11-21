# ECS Demo - Visual Documentation

Since this is running in a headless environment, here's what the ECS Demo window displays:

## Main Window: "ECS Demo Info"
```
┌─────────────────────────────────────┐
│ ECS Demo Info                       │
├─────────────────────────────────────┤
│ FPS: 60.0                           │
│ Delta Time: 16.667 ms               │
│ ─────────────────────────────────── │
│ Entities: 3                         │
│ Systems: 2 (Physics, Rotation)      │
│ [ Reset Positions ]                 │
└─────────────────────────────────────┘
```

## Main Window: "ECS Debugger"
```
┌──────────────────────────────────────────────────────────┐
│ ECS Debugger                                              │
├──────────────────────────────────────────────────────────┤
│ Tabs: [Entities] [Systems] [Statistics]                  │
├──────────────────────────────────────────────────────────┤
│                                                           │
│ === Entities Tab ===                                     │
│ Total Entities: 3                                        │
│ ─────────────────────────────                            │
│ > Moving Box                                             │
│   Signature: 0000000000000000000000000000000000001111    │
│   Components:                                            │
│   • Position: (5.00, 2.50, 0.00)                        │
│     ► Edit Position                                      │
│       X: [5.00     ] ◄──►                               │
│       Y: [2.50     ] ◄──►                               │
│       Z: [0.00     ] ◄──►                               │
│   • Velocity: (2.00, 1.00, 0.00)                        │
│     ► Edit Velocity                                      │
│   • Rotation: (0.00, 225.00, 0.00)                      │
│     ► Edit Rotation                                      │
│   • Name: Moving Box                                     │
│                                                           │
│ > Rotating Sphere                                        │
│   Signature: 0000000000000000000000000000000000001010    │
│   Components:                                            │
│   • Position: (5.00, 2.00, 0.00)                        │
│   • Rotation: (0.00, 225.00, 0.00)                      │
│   • Name: Rotating Sphere                                │
│                                                           │
│ > Fast Particle                                          │
│   Signature: 0000000000000000000000000000000000001011    │
│   Components:                                            │
│   • Position: (10.00, -3.50, 1.50)                      │
│   • Velocity: (3.00, -1.00, 0.50)                       │
│   • Name: Fast Particle                                  │
│                                                           │
└──────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────┐
│ === Systems Tab ===                                      │
│ Registered Systems:                                      │
│ ─────────────────────────────                            │
│ ▼ PhysicsSystem                                          │
│   Entities: 2                                            │
│   ► Entity List                                          │
│     • Entity 1                                           │
│     • Entity 3                                           │
│                                                           │
│ ▼ RotationSystem                                         │
│   Entities: 2                                            │
│   ► Entity List                                          │
│     • Entity 1                                           │
│     • Entity 2                                           │
└──────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────┐
│ === Statistics Tab ===                                   │
│ ECS Statistics                                           │
│ ─────────────────────────────                            │
│ Total Entities: 3                                        │
│ Tracked Entities: 3                                      │
│ Systems: 2                                               │
│ ─────────────────────────────                            │
│ Memory Usage (estimated):                                │
│   Entity overhead: ~24 bytes                             │
└──────────────────────────────────────────────────────────┘
```

## Features Demonstrated

1. **Real-time Entity Inspection**
   - Click on any entity to select it
   - View all components and their current values
   - See entity signatures (bitset showing which components are attached)

2. **Live Component Editing**
   - Expand component sections to see sliders
   - Drag sliders to modify values in real-time
   - Changes immediately affect simulation

3. **System Monitoring**
   - View all registered systems
   - See which entities each system processes
   - Monitor entity counts per system

4. **Statistics**
   - Real-time entity count
   - Memory usage estimates
   - System count

5. **Interactive Controls**
   - Reset button to restore initial positions
   - ESC key to exit demo
   - ImGui demo window for reference

## Key Interactions

- **PhysicsSystem**: Updates position based on velocity for entities with both components
- **RotationSystem**: Rotates entities that have a Rotation component
- Entities are updated at 60 FPS with real-time visualization in the debugger
- Component values can be edited while the simulation is running

# Systems

## Core Systems

Order:
Events > [ Time/TimerUpdate ] > Animator(TimeRemap) {TimedAnim} > SceneHierarchy {Parent} > Renderer {Mesh<>Material}

### Animator

Components: TimedAttr, TimedTranform

### SceneHierarchy

Components: TransformLink, PositionLink, OrientationLink

### Renderer

Components: Material (MaterialId, linked to RawMesh)

# Systems

## Core Systems

Order:
Events > [ Time/TimerUpdate ] > Animator(TimeRemap) {TimedAnim} > SceneHierarchy {Parent} > Renderer {Mesh<>Material} (then update screen with rendered Framebuffer)

### Animator

Components: TimedAttr, TimedTranform

### SceneHierarchy

Components: TransformLink, PositionLink, OrientationLink

### Renderer

Components: Material (MaterialId, linked to RawMesh)

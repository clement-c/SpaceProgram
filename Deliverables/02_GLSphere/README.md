# Deliverable 2 - GLSphere

Entities:
- Camera
  + localXfo
  + fov
- DebugSphere
  + localXfo: Xform
  + radius: float

- User input
- Systems:
  + UserInput ?
  + Scene/Transform
  + Render


Systems order and dependencies
1. UserInput/EventsProcess
2. SceneAssembly/Cull (pre build matrix multiplication chains, instances, etc)
4. SceneHierarchyTransform
5. RenderCull (1 cull per camera)
6. Render (1 render per camera/surface pair)


## TODO

- Events
  - [ ] Window resize, glViewport
  - [ ] App events / actions
  - [ ] User action tied to events (key press)
- Drawables
  - [ ] Drawable entity
  
Drawable Entity limitation in this delierable:
Create Components from data inside deliverable, use resource loading + static entities later.
Resize is a recreation of a new entity rather than updating existing one

Input limitations:
Using raw input, no clever mapping or repeatability

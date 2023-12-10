# Deliverable 2 - GLSphere

Entities:
- DebugSphere
  + localXfo: Xform
  + radius: float
- Camera
  + localXfo
  + fov

- User input
- Systems:
  + UserInput ?
  + Scene
  + Render


Systems order and dependencies
1. UserInput/EventsProcess
2. SceneAssembly/Cull (pre build matrix multiplication chains, instances, etc)
4. SceneHierarchyTransform
5. RenderCull (1 cull per camera)
6. Render (1 render per camera)



## TODO

- Events
  - [ ] Window resize, glViewport
  - [ ] App events / actions
  - [ ] User action tied to events (key press, key hold)
- Animation
  - [ ] Ease in / out interpolation, time normalization from an epoch
- Drawables
  - [ ] Drawable object (to be transformed into an Entity/Component later)

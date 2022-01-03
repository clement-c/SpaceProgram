# Deliverable 1 - Simple triangle window

![only though](img/screenshot.png)

Not really a deliverable for clients, but the first pass to organize the project.

### :page_facing_up: Features
- OpenGL raw classes, GL 4.5 only, Windows only
- Application / WindowsManager classes
- Application main loop
- Logging using macros
- Basic support for multiple windows

### :electric_plug: Libraries

- OpenGL is loaded with *glad*
- Windows are created using *glfw*
- Logging uses *fmt*

### :warning: Shortcomings / Ideas of improvements
- Haven't implemented window resize callback
- Implementation of GL VAO/Buffers is very much specific for this deliverable, not sure it will be kept when implementing Meshes / draw system.

### :pensive: Questions / Concerns
- Glad is custom-compiled as a DLL, and linked both to the Engine DLL and the exe. It is loaded in Engine.dll. Could cause issues especially for Windows (couldn't find a way to add glad to Engine.dll only)

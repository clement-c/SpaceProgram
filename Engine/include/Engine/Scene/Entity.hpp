#pragma once
#include <stdint.h>

/*
Entity has multiple components
RenderBuffer
{
    something = [],
    other = false
}
Transform
{
    base = [1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0]
}
*/

class Component;

class Entity
{
public:

    using EntityId = uint32_t;

    // enum Scene
    // {
    //     k3dMeshInstancer,
    //     k3dMeshTransform
    // };

    // enum class Gizmo3D
    // {
    //     // kManipulator,
    //     kCamera,
    //     // kCapsule,
    //     // kDebugCube,
    //     kDebugSphere
    // };

    // enum class Gizmo2D
    // {
    //     kButton,
    //     kLabel,
    //     kLineEdit,
    //     kSlider
    // };

private:
    // std::vector<Component*> m_components;
};

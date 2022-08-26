#include "../../StaticEntity.hpp"

struct Camera : public StaticEntity
{
    Camera();
};

struct PerspectiveCamera : public Camera
{
    PerspectiveCamera(float fov, float aspectRatio, float nearPlane = 0.1, float farPlane = 1000.0);
    // Transform component
};

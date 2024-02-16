#pragma once

#include <cmath>

#include "Engine/Core/Logging.hpp"

#include "Engine/Runtime/Camera.hpp"
#include "Engine/Core/Maths/Constants.hpp"

// TEMP:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {}
Camera::Camera(float aspectRatio) : m_aspectRatio{aspectRatio} {}
Camera::Camera(float fov, float nearPlane, float farPlane, float aspectRatio) : m_fov{fov}, m_nearPlane{nearPlane}, m_farPlane{farPlane}, m_aspectRatio{aspectRatio}
{
}

Matrix44 Camera::GetProjectionMatrix()
{
    // if(m_dirtyProjection)
    // {
    auto persp = glm::perspective(glm::radians(m_fov), 1920.0f/1080.0f, 0.1f, 100.0f);
    m_projectionMatrix = *(Matrix44*)(&persp);
    // }
    return m_projectionMatrix;
}

void Camera::SetViewMatrix(Matrix44 const &mat)
{
    m_viewMatrix = mat;
}
Matrix44 Camera::GetViewMatrix()
{
    return m_viewMatrix;
}

Matrix44 Camera::GetProjectionViewMatrix()
{
    return GetViewMatrix() * GetProjectionMatrix();
}

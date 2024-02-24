#pragma once

#include <cmath>

#include "Engine/Core/Logging.hpp"

#include "Engine/Runtime/Camera.hpp"
#include "Engine/Core/Maths/Constants.hpp"

Camera::Camera() {}
Camera::Camera(float fov, float nearPlane, float farPlane) : m_fov{fov}, m_nearPlane{nearPlane}, m_farPlane{farPlane} {}

float Camera::GetFOV() { return m_fov; }
Camera &Camera::SetFOV(float fov_degrees)
{
    m_fov = fov_degrees;
    m_dirtyProjection = true;
    return *this;
}

float Camera::GetNearPlane() { return m_nearPlane; }
Camera &Camera::SetNearPlane(float near_plane)
{
    m_nearPlane = near_plane;
    m_dirtyProjection = true;
    return *this;
}

float Camera::GetFarPlane() { return m_farPlane; }
Camera &Camera::SetFarPlane(float far_plane)
{
    m_farPlane = far_plane;
    m_dirtyProjection = true;
    return *this;
}

Matrix44 Camera::GetProjectionMatrix(float aspectRatio)
{
    float const tan_half_fov = tan(m_fov / 2.0f);

    m_projectionMatrix = Matrix44::Identity();
    m_projectionMatrix[0][0] = 1.0f / (aspectRatio * tan_half_fov);
    m_projectionMatrix[1][1] = 1.0f / (tan_half_fov);
    m_projectionMatrix[2][2] = -(m_farPlane + m_nearPlane) / (m_farPlane - m_nearPlane);
    m_projectionMatrix[2][3] = -1.0f;
    m_projectionMatrix[3][2] = -(2.0f * m_farPlane * m_nearPlane) / (m_farPlane - m_nearPlane);

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

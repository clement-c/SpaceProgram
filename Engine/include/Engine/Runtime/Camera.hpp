#pragma once

#include "../Core/Lib.hpp"
#include "../Core/Maths/Matrix44.hpp"

struct Camera
{
public:
    DLLEXPORT Camera();
    DLLEXPORT Camera(Matrix44 const& viewMatrix) : m_viewMatrix{viewMatrix} {}
    DLLEXPORT Camera(float aspectRatio);
    DLLEXPORT Camera(float fov, float nearPlane, float farPlane, float aspectRatio);

	// Projection attributes
	DLLEXPORT float GetFOV();
	DLLEXPORT Camera& SetFOV(float fov_degrees);
	DLLEXPORT float GetNearPlane();
	DLLEXPORT Camera& SetNearPlane(float near_plane);
	DLLEXPORT float GetFarPlane();
	DLLEXPORT Camera& SetFarPlane(float far_plane);
	DLLEXPORT float GetAspectRatio();
	DLLEXPORT Camera& SetAspectRatio(float aspect_ratio);

	DLLEXPORT Matrix44 GetProjectionMatrix();

	DLLEXPORT void SetViewMatrix(Matrix44 const& mat);
	DLLEXPORT Matrix44 GetViewMatrix();

	DLLEXPORT Matrix44 GetProjectionViewMatrix();

private:
	float m_fov = 45.f;
	float m_nearPlane = 0.1f;
	float m_farPlane = 1000.0f;
	float m_aspectRatio = 1.0f;

	bool m_dirtyProjection = true;
	bool m_dirtyView = true;

    // position
	Matrix44 m_projectionMatrix;
	Matrix44 m_viewMatrix;

	// Matrix4f viewMatrix = new Matrix4f();
	// Matrix4f projectionViewMatrix = new Matrix4f();
};

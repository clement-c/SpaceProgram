#pragma once

#include "../Core/Lib.hpp"
#include "../Core/Maths/Matrix44.hpp"

struct Camera
{
public:
	DLLEXPORT Camera();
	DLLEXPORT Camera(Matrix44 const &viewMatrix) : m_viewMatrix{viewMatrix} {}
	DLLEXPORT Camera(float fov, float nearPlane, float farPlane);

	// Projection attributes
	DLLEXPORT float GetFOV();
	DLLEXPORT Camera &SetFOV(float fov_degrees);
	DLLEXPORT float GetNearPlane();
	DLLEXPORT Camera &SetNearPlane(float near_plane);
	DLLEXPORT float GetFarPlane();
	DLLEXPORT Camera &SetFarPlane(float far_plane);

	DLLEXPORT Matrix44 GetProjectionMatrix(float aspectRatio);
	DLLEXPORT Matrix44 GetProjectionMatrix(float width, float height) { return GetProjectionMatrix(width / height); }

	DLLEXPORT void SetViewMatrix(Matrix44 const &mat) { m_viewMatrix = mat; m_dirtyView = true; }
	/**
	 * @brief Set the transfor of the camera, must be an orthonormal matrix
	 * 
	 * @param mat 
	 * @return DLLEXPORT 
	 */
	DLLEXPORT void SetMatrix(Matrix44 const &mat);
	DLLEXPORT Matrix44 GetViewMatrix();

private:
	float m_fov = 45.f;
	float m_nearPlane = 0.1f;
	float m_farPlane = 1000.0f;

	bool m_dirtyProjection = true;
	bool m_dirtyView = true;

	// position
	Matrix44 m_projectionMatrix;
	Matrix44 m_viewMatrix;
};

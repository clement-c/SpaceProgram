#pragma once

struct Camera
{
public:
    Camera() = delete;
    Camera(float aspectRation);
    Camera(float fov, float nearPlane, float farPlane, float aspectRatio, float wideAspectThreshold);

private:
	float m_fov = 40.f;
	float m_nearPlane = 0.1f;
	float m_farPlane = 1000.0f;
	float m_aspectRatio = 1.0f;

	bool m_dirtyProjection = true;
	bool m_dirtyView = true;

    // position
	// Matrix4f projectionMatrix = new Matrix4f();
	// Matrix4f viewMatrix = new Matrix4f();
	// Matrix4f projectionViewMatrix = new Matrix4f();
};

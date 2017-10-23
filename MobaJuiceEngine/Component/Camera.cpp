#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>
Camera * Camera::main = nullptr;

Camera::Camera(std::string name) : Behaviour(name)
{
	if (Camera::main == nullptr)
		Camera::main = this;
}

Camera::~Camera()
{
}

void Camera::SetFOV(float _fov)
{
	fov = _fov;
	SetPerspective(fov, aspectRatio, near, far);
}

void Camera::SetClippingPlanes(float _near, float _far)
{
	near = _near;
	far = _far;

	SetPerspective(fov, aspectRatio, near, far);
}

void Camera::SetFarClippingPlane(float _far)
{
	SetClippingPlanes(near, _far);
}

void Camera::SetNearClippingPlane(float _near)
{
	SetClippingPlanes(_near, far);
}

void Camera::SetPerspective(float _fov, float _aspectRatio, float _near, float _far)
{
	projection = perspective(_fov, _aspectRatio, _near, _far);
}

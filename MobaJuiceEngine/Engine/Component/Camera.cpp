#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>
#include "..\Transform.h"
#include "..\GameObject.h"
namespace Engine {
	Camera * Camera::mainCamera = nullptr;

	Camera::Camera(std::string name) : Behaviour(name)
	{
		if (Camera::mainCamera == nullptr)
			Camera::mainCamera = this;

		SetPerspective(fov, aspectRatio, near, far);
	}

	Camera::Camera()
	{
		if (Camera::mainCamera == nullptr)
			Camera::mainCamera = this;

		SetPerspective(fov, aspectRatio, near, far);
	}

	Camera::~Camera()
	{
	}

	Camera * Camera::Create(GameObject * gameObject)
	{
		Camera *c = new Camera();
		gameObject->AddComponent(c);
		return c;
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

	mat4 Camera::GetViewMatrix()
	{
		return view;
	}

	mat4 Camera::GetProjectionMatrix()
	{
		return projection;
	}

	void Camera::Update()
	{
		CalculateViewMatrix();
	}

	void Camera::CalculateViewMatrix() // GetView();
	{
		view = lookAt(transform->GetPosition(), transform->GetPosition() + transform->Front(), transform->Up());
	}

	void Camera::SetPerspective(float _fov, float _aspectRatio, float _near, float _far)
	{
		fov = _fov;
		aspectRatio = _aspectRatio;
		near = _near;
		far = _far;
		projection = perspective(radians(_fov), (float)_aspectRatio, _near, _far);
	}
}

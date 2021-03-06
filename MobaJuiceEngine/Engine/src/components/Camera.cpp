#include "components\Camera.h"
#include <glm\gtc\matrix_transform.hpp>
#include "core\Transform.h"
#include "core\GameObject.h"
namespace Engine {
	Camera * Camera::mainCamera = nullptr;

	Camera::Camera(std::string name) : Behaviour(name)
	{
		if (Camera::mainCamera == nullptr)
			Camera::mainCamera = this;

		front = vec3(0, 0, 1);
	}

	Camera::Camera()
	{
		if (Camera::mainCamera == nullptr)
			Camera::mainCamera = this;

		front = vec3(0, 0, 1);
	}

	Camera::~Camera()
	{
	}

	Camera * Camera::Create(GameObject * gameObject)
	{
		Camera *c = new Camera();
		gameObject->AddComponent(c);
		c->front = vec3(0, 0, 1);
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

	void Camera::SetViewMatrix(mat4 viewMatrix)
	{
		view = viewMatrix;
	}

	mat4 Camera::GetProjectionMatrix()
	{
		return projection;
	}

	mat4 Camera::SetProjectionMatrix(mat4 projection)
	{
		return this->projection = projection;;
	}

	void Camera::OnLoad()
	{
		SetPerspective(fov, aspectRatio, near, far);
	}

	void Camera::Update()
	{
		CalculateViewMatrix();
	}

	void Camera::CalculateViewMatrix() // GetView();
	{
		if (!customViewMatrix)
		{
			view = lookAt(transform->GetPosition(), transform->GetPosition() - transform->Front(), transform->Up());
		}
		
	}

	void Camera::Copy(GameObject * copyObject)
	{
		Camera * copy = new Camera();
		copy->projection = Camera::projection;
		copy->view = Camera::view;
		copy->front = Camera::front;
		copy->up = Camera::up;
		copy->fov = Camera::fov;
		copy->aspectRatio = Camera::aspectRatio;
		copy->near = Camera::near;
		copy->far = Camera::far;

		copyObject->AddComponent(copy);
	}

	float Camera::GetFOV()
	{
		return fov;
	}

	float Camera::GetAspectRatio()
	{
		return aspectRatio;
	}

	float Camera::GetNear()
	{
		return near;
	}

	float Camera::GetFar()
	{
		return far;
	}

	vec3 Camera::GetFront()
	{
		return front;
	}

	void Camera::SetFront(vec3 front)
	{
		this->front = front;
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

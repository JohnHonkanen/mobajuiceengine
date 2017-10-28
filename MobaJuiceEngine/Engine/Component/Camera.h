/*
	Camera class for the game engine
	Dev: John Honkanen
*/

#pragma once
#include "../Behaviour.h"
#include <memory>
#include<glm\glm.hpp>

using namespace glm;
class Camera : public Behaviour
{
public:
	Camera(std::string name);
	~Camera();

	//Current Active camera
	static Camera* mainCamera;
	/*
		Creates a perspective matrix for the camera
		@param _fov			Field of view of the camara
		@param _aspectRatio	Aspect ratio of the camera
		@param _near		Near plane distance of the camera clipping
		@param _far			Far plane distance of the camerae clipping
	*/
	void SetPerspective(float _fov, float _aspectRatio, float _near, float _far);
	/*
		Set FOV
		@param _fov	Field of View
	*/
	void SetFOV(float _fov);
	/*
		Set the near and far plane distance
		@param _near	near plane distance of the fustrum
		@param _far		far plane distance of the fustrum
	*/
	void SetClippingPlanes(float _near, float _far);
	/*
		Set the far plane
		@param _far	Far plane distance of the fustrum
	*/
	void SetFarClippingPlane(float _far);
	/*
		Set the near plane
		@param _near	near plane distance of the fustrum
	*/
	void SetNearClippingPlane(float _near);

	/*
		Get the view matrix
	*/
	mat4 GetViewMatrix();
	/*
		Get the projection matrix
	*/

	mat4 GetProjectionMatrix();

	void Update();

private:
	/*
		Calculates the view matrix of the camera
	*/
	void CalculateViewMatrix();
	mat4 projection;
	mat4 view;

	vec3 front;
	vec3 up;

	float fov = 45.0f;
	float aspectRatio = float(4/3);
	float near = 0.01f;
	float far = 100.0f;

};
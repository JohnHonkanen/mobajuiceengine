/*
	Camera class for the game engine
	Dev: John Honkanen
*/
#pragma once
#include "../Behaviour.h"
#include <memory>
#include<glm\glm.hpp>

using namespace glm;
namespace Engine {
	class Camera : public Behaviour
	{
	public:
		Camera(std::string name);
		Camera();
		~Camera();

		//Current Active camera
		static Camera* mainCamera;
		/*
			Sets up the Camera and its dependicies. Make the gameObject the owner of this component
			@param gameObject	Object that owns this Behaviour
			@return				The created Camera gameObject
		*/
		static Camera* Create(GameObject *gameObject);
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

		/*
		Calculates the view matrix of the camera
		*/
		void CalculateViewMatrix();

	private:
		
		mat4 projection;
		mat4 view;

		vec3 front;
		vec3 up;

		float fov = 45.0f;
		float aspectRatio = float(16.0f / 9.0f);
		float near = 1.0f;
		float far = 100.0f;

	};
}
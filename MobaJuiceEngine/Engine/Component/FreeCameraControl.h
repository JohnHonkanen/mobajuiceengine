#pragma once
#include "../Behaviour.h"
#include <glm\glm.hpp>


namespace Engine {
	class Camera;
	class GameObject;
	class InputManager;
	class FreeCameraControl : Behaviour
	{
	public:
		FreeCameraControl();
		~FreeCameraControl();

		void MoveCamera();
		void OnLoad();
		void Update(float dt);
		void Input();
		static FreeCameraControl* Create(GameObject* gameObject);

	private:
		InputManager *inputManager;
		Camera* camera;
		glm::vec3 movement;
		int rotate; 
		//glm::vec3 tempMovement = glm::vec3(0);

		float dt = 0.1f;
		int tempRotate = 0;
		float cameraSpeed = 7.5f;
		float cameraRotateSpeed = 1.5f;

		float lastX = 640.0f;
		float lastY = 360.0f;

		float yaw;
		float pitch;
	};
}

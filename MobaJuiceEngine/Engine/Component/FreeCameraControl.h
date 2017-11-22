#pragma once
#include "../Behaviour.h"
#include <glm\glm.hpp>

namespace Engine {
	class Camera;
	class FreeCameraControl : Behaviour
	{
	public:
		FreeCameraControl();
		~FreeCameraControl();

		void MoveCamera(SDL_Event* sdlEvent);
		void Update(float dt);
	private:
		Camera camera;
		glm::vec3 movement;
		int rotate; 
		glm::vec3 tempMovement = glm::vec3(0);

		float dt = 0.1f;
		int tempRotate = 0;
		float cameraSpeed = 7.5f;
		float cameraRotateSpeed = 1.5f;

		float lastX = 640.0f;
		float lastY = 360.0f;

		float yaw;
		float pitch;
		int mouseX, mouseY;
	};
}

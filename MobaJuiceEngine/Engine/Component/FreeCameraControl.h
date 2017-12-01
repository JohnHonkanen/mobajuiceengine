#pragma once
#include "../Behaviour.h"
#include <glm\glm.hpp>
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>

namespace Engine {
	class Camera;
	class GameObject;
	class InputManager;
	class FreeCameraControl : public Behaviour
	{
	public:
		FreeCameraControl();
		~FreeCameraControl();

		void MoveCamera();
		void OnLoad();
		void Update();
		void Input();
		static FreeCameraControl* Create(GameObject* gameObject);

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(yaw), CEREAL_NVP(pitch));
		}


	private:
		InputManager *inputManager;
		Camera* camera;
		glm::vec3 movement;
		int rotate; 
		//glm::vec3 tempMovement = glm::vec3(0);

		bool freezeMouse = false;
		int tempRotate = 0;
		float cameraSpeed = 7.5f;
		float cameraRotateSpeed = 1.5f;

		float lastX = 640.0f;
		float lastY = 360.0f;

		float yaw;
		float pitch;
	};
}

using namespace Engine;


#include <cereal/archives/xml.hpp>
//Register camera as a derived class
CEREAL_REGISTER_TYPE(FreeCameraControl);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, FreeCameraControl);
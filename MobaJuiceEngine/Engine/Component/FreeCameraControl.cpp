#include "FreeCameraControl.h"
#include <glm\gtx\compatibility.hpp>
#include <iostream>
#include "Camera.h"
#include "..\InputManager.h"
#include "..\GameObject.h"
#include "..\GameEngine.h"

namespace Engine {

	FreeCameraControl::FreeCameraControl()
	{
	}

	FreeCameraControl::~FreeCameraControl()
	{
	}

	void FreeCameraControl::MoveCamera()
	{
		bool mouseMotion = inputManager->CheckMouseMotion();

		if (!mouseMotion || freezeMouse) {
			return;
		}

		int mouseX, mouseY;
		inputManager->GetMousePos(mouseX, mouseY);

		float xoffset = mouseX - lastX;
		float yoffset = lastY - mouseY; // Reversed since y-coordinate range from bottom to top.

		glm::vec2 mouseDir(xoffset, yoffset);

		lastX = mouseX;
		lastY = mouseY;

		float mouseSensitivity = 0.05f;
		float smoothing = 2.0f;

		mouseDir = mouseDir * vec2(mouseSensitivity * smoothing);
		glm::vec2 smoothV;

		smoothV.x = glm::lerp(smoothV.x, mouseDir.x, 1.0f / smoothing);
		smoothV.y = glm::lerp(smoothV.y, mouseDir.y, 1.0f / smoothing);

		yaw -= smoothV.x;
		pitch -= smoothV.y;

		pitch = glm::clamp(pitch, -100.0f, 100.0f);
		transform->SetEulerAngle(glm::vec3(pitch, yaw, 0.0f));

		lastX = 640.0f;
		lastY = 360.0f;

	}

	void FreeCameraControl::OnLoad()
	{
		inputManager = &GameEngine::manager.inputManager;
	}

	void FreeCameraControl::Update()
	{
		float dt = 0.17f;
		transform->Translate(((transform->Front() * movement.z) + (transform->Right() * -movement.x)) * dt * cameraSpeed);

	}

	void FreeCameraControl::Input()
	{
		// Horizontal
		int h = inputManager->GetKey("Horizontal");

		// Vertical
		int v = inputManager->GetKey("Vertical");

		movement = vec3(h, 0, v);

		if (inputManager->GetKey("FreezeMouse")) {
			freezeMouse = true;
		}

		if (inputManager->GetKey("FreezeMouse") == -1) {
			freezeMouse = false;
		}
		MoveCamera();
	}

	FreeCameraControl* FreeCameraControl::Create(GameObject* gameObject)
	{	
		FreeCameraControl *f = new FreeCameraControl();
		gameObject->AddComponent(f);
		return f;
	}

}
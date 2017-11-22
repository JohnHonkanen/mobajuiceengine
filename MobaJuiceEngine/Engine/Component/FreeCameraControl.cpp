#include "FreeCameraControl.h"
#include <SDL.h>
#include <glm\gtx\compatibility.hpp>
#include <iostream>
#include "Camera.h"
#include "..\InputManager.h"
#include "..\GameObject.h"

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

		if (!mouseMotion) {
			return;
		}

		int mouseX, mouseY;
		inputManager->GetMousePos(mouseX, mouseY);

		float xoffset = mouseX - lastX;
		float yoffset = lastY - mouseY; // Reversed since y-coordinate range from bottom to top.

		glm::vec2 mouseDir(xoffset, yoffset);

		lastX = mouseX;
		lastY = mouseY;

		float mouseSensitivity = 0.1f;
		float smoothing = 2.0f;

		mouseDir = mouseDir * vec2(mouseSensitivity * smoothing);
		glm::vec2 smoothV;

		smoothV.x = glm::lerp(smoothV.x, mouseDir.x, 1.0f / smoothing);
		smoothV.y = glm::lerp(smoothV.y, mouseDir.y, 1.0f / smoothing);

		yaw -= smoothV.x;
		pitch += smoothV.y;

		pitch = glm::clamp(pitch, -91.0f, 91.0f);
		transform->SetEulerAngle(glm::vec3(glm::radians(pitch), glm::radians(yaw), 0.0f));

		lastX = 640.0f;
		lastY = 360.0f;

	}

	void FreeCameraControl::Update(float dt)
	{
		Input();
		transform->Translate(((transform->Front() * movement.z) + (transform->Right() * movement.x)) * dt * cameraSpeed);

	}

	void FreeCameraControl::Input()
	{
		// Horizontal
		int h = inputManager->GetKey("Horizontal");

		// Vertical
		int v = inputManager->GetKey("Vertical");

		movement = vec3(h, 0, v);
	}

	FreeCameraControl* FreeCameraControl::Create(GameObject* gameObject, InputManager* inputManager)
	{	
		FreeCameraControl *f = new FreeCameraControl();
		f->inputManager = inputManager;
		gameObject->AddComponent(f);
		return f;
	}

}
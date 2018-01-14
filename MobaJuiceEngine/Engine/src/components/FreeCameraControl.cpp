#include "components\FreeCameraControl.h"
#include <glm\gtx\compatibility.hpp>
#include <iostream>
#include "components\Camera.h"
#include "core\InputManager.h"
#include "core\GameObject.h"
#include "core\GameEngine.h"

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

		int xoffset = mouseX - lastX;
		int yoffset = lastY - mouseY; // Reversed since y-coordinate range from bottom to top.

		inputManager->GetMouseMotion(xoffset, yoffset);

		yoffset = -yoffset;

		glm::vec2 mouseDir(xoffset, yoffset);

		lastX = mouseX;
		lastY = mouseY;

		float mouseSensitivity = 0.5f;
		float smoothing = 2.0f;

		mouseDir = mouseDir * vec2(mouseSensitivity * smoothing);
		glm::vec2 smoothV;

		smoothV.x = glm::lerp(smoothV.x, mouseDir.x, 1.0f / smoothing);
		smoothV.y = glm::lerp(smoothV.y, mouseDir.y, 1.0f / smoothing);

		yaw -= smoothV.x;
		pitch -= smoothV.y;

		pitch = glm::clamp(pitch, -100.0f, 100.0f);
		transform->SetEulerAngle(glm::vec3(pitch, yaw, 0.0f));

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

	void FreeCameraControl::Copy(GameObject * copyObject)
	{
		FreeCameraControl *copy = new FreeCameraControl();

		copy->pitch = FreeCameraControl::pitch;
		copy->yaw = FreeCameraControl::yaw;
		copy->cameraSpeed = FreeCameraControl::cameraSpeed;
		copy->cameraRotateSpeed = FreeCameraControl::cameraRotateSpeed;

		copyObject->AddComponent(copy);
	}

}
#include "FreeCameraControl.h"
#include <SDL.h>
#include <glm\gtx\compatibility.hpp>
#include <iostream>
#include "Camera.h"

Engine::FreeCameraControl::FreeCameraControl()
{
}

Engine::FreeCameraControl::~FreeCameraControl()
{
}

void Engine::FreeCameraControl::MoveCamera(SDL_Event* sdlEvent)
{
	if (sdlEvent->type == SDL_MOUSEMOTION || sdlEvent->type == SDL_MOUSEBUTTONDOWN || sdlEvent->type == SDL_MOUSEBUTTONUP) {
	//Get Mouse Position
	
	SDL_GetMouseState(&mouseX, &mouseY);

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

	movement = tempMovement;
	rotate = tempRotate;

	}
}

void Engine::FreeCameraControl::Update(float dt)
{
	transform->Translate(((transform->Front() * movement.z) + (transform->Right() * movement.x)) * dt * cameraSpeed);

	transform->Rotate(glm::vec3(0.0f, 1.0f, 0.0f) * float(rotate) * dt * cameraRotateSpeed);
}

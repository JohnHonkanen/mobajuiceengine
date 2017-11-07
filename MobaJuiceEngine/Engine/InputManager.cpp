#include "InputManager.h"

Engine::InputManager::InputManager()
{
}

Engine::InputManager::~InputManager()
{
}

void Engine::InputManager::Update()
{
	SDL_GetMouseState(&mouseX, &mouseY);

}

void Engine::InputManager::GetMousePos(int &x, int &y)
{
	x = mouseX;
	y = mouseY;
}

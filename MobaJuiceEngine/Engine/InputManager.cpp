#include "InputManager.h"
#include <iostream>

using namespace std;

Engine::InputManager::InputManager()
{
}

Engine::InputManager::~InputManager()
{
}

void Engine::InputManager::Update(bool & running)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	SDL_Event sdlEvent;

	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_QUIT) {
			running = false;
		}

		if (sdlEvent.type == SDL_KEYDOWN) {
			switch (sdlEvent.key.keysym.sym) {

			case SDLK_ESCAPE:
				cout << "Program exit" << endl;
				running = false;
				break;
			case SDLK_a:
				cout << "A pressed" << endl;
				break;

			default:
				cout << "Default called" << endl;
				break;
			}
		}
	}
}

void Engine::InputManager::GetMousePos(int &x, int &y)
{
	x = mouseX;
	y = mouseY;
}

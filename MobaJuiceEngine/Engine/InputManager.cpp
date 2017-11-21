#include "InputManager.h"
#include <iostream>

using namespace std;

Engine::InputManager::InputManager(string k)
{
	k = key;
}

Engine::InputManager::~InputManager()
{
}

void Engine::InputManager::Update(bool & running)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

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

int Engine::InputManager::GetKey(string key)
{
	auto iterator = keys.find(key);

	if (iterator != keys.end()) {
		return keys[key];
	}

	// Create new key

	SetKey(key); // Save it
	return keys[key];
}

void Engine::InputManager::SetKey(const string key)
{
	int keyString; 

	keys.insert(keys.end(), pair<string, int>(key, keyString));

}

#include "InputManager.h"
#include <iostream>
#include "SDLKeyMapper.h"
#include <assert.h>

using namespace std;

Engine::InputManager::InputManager()
{
	InitKeyMap();
}

Engine::InputManager::~InputManager()
{
}

void Engine::InputManager::Update(bool & running)
{
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
			}
		}
		const Uint8 *keys = SDL_GetKeyboardState(NULL);
		QueryKeys(keys);
	}
}

void Engine::InputManager::GetMousePos(int &x, int &y)
{
	x = mouseX;
	y = mouseY;
}

int Engine::InputManager::GetKey(string key)
{

	// If exists
	if (axis.find(key) != axis.end()) {
		return axis[key].GetValue();
	}

	assert(0); // Key not found
	return 0;
}

void Engine::InputManager::AddKey(string name, string positive, string negative)
{
	// If exists
	if (axis.find(name) != axis.end()) {
		assert(0); // Already exists (Duplicate)
	}

	// Else, create
	KeyAxis keyAxis = KeyAxis(name, positive, negative);

	axis[name] = keyAxis;
}

void Engine::InputManager::QueryKeys(const Uint8 *keys)
{
	for (auto it = axis.begin(); it != axis.end(); ++it) {
		string positive, negative;
		it->second.GetKeys(positive, negative);

		int pos, neg;
		pos = 0;
		neg = 0;

		if (keys[keyMap[positive]]) {
			pos = 1;
		}

		if (keys[keyMap[negative]]) {
			neg = 1;
		}

		it->second.SetPress(pos, neg);
	}
}

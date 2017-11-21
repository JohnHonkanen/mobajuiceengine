#pragma once

#include <SDL.h>
#include <map>
#include <string>

namespace Engine {

	class InputManager
	{
	public:
		InputManager(std::string key);
		~InputManager();

		void Update(bool &running);
		void GetMousePos(int &x, int &y);

		int GetKey(std::string key);
		void SetKey(const std::string key);
	private:

		std::string key;
		int mouseX, mouseY;

		std::map<std::string, int> keys;
		SDL_Event sdlEvent;
	};
}
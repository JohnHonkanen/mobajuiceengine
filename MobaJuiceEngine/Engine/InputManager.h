#pragma once

#include <SDL.h>
#include <map>
#include <string>
#include "KeyAxis.h"


namespace Engine {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void Update(bool &running);
		void GetMousePos(int &x, int &y);
		bool CheckMouseMotion();

		int GetKey(std::string name);
		void AddKey(string name, string positive, string negative);
		void AddKey(string name, string positive);

	private:
		SDL_Event sdlEvent;
		void QueryKeys(const Uint8 *keys, const Uint8 *mouseButton);
		std::string key;
		int mouseX, mouseY;
		
		bool mouseMotion = false;

		map<string, Uint8> keyMap;
		map<string, Uint8> mouseMap;

		std::map<std::string, KeyAxis> axis;
		

	};
}
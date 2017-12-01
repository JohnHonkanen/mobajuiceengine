#pragma once

#include <SDL.h>
#include <map>
#include <string>
#include <cereal\cereal.hpp>
#include <cereal\types\map.hpp>
#include "KeyAxis.h"


namespace Engine {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void Update(bool &running, SDL_Window* window);
		void GetMousePos(int &x, int &y);
		bool CheckMouseMotion();

		int GetKey(std::string name);
		void AddKey(string name, string positive, string negative);
		void AddKey(string name, string positive);

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(axis));
		}

	private:
		SDL_Event sdlEvent;
		void QueryKeys(const Uint8 *keys, const Uint8 *mouseButton);
		std::string key;
		int mouseX, mouseY;
		
		bool mouseMotion = false;
		bool centerMouse = true;
		map<string, Uint8> keyMap;
		map<string, Uint8> mouseMap;

		std::map<std::string, KeyAxis> axis;
		

	};
}
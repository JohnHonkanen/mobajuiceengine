#pragma once
#include <map>
#include <string>
#include <SDL.h>

using namespace std;
namespace Engine {
	void InitKeyMap(map<string, Uint8> &keyMap, map<string, Uint8> &mouseMap) {
		keyMap["a"] = 4;
		keyMap["b"] = 5;
		keyMap["c"] = 6;
		keyMap["d"] = 7;
		keyMap["e"] = 8;
		keyMap["f"] = 9;
		keyMap["g"] = 10;
		keyMap["h"] = 11;
		keyMap["i"] = 12;
		keyMap["j"] = 13;
		keyMap["k"] = 14;
		keyMap["l"] = 15;
		keyMap["m"] = 16;
		keyMap["n"] = 17;
		keyMap["o"] = 18;
		keyMap["p"] = 19;
		keyMap["q"] = 20;
		keyMap["r"] = 21;
		keyMap["s"] = 22;
		keyMap["t"] = 23;
		keyMap["u"] = 24;
		keyMap["v"] = 25;
		keyMap["w"] = 26;
		keyMap["x"] = 27;
		keyMap["y"] = 28;
		keyMap["z"] = 29;

		mouseMap["mouse0"] = SDL_BUTTON_LEFT; // Left
		mouseMap["mouse1"] = SDL_BUTTON_RIGHT; // Right
		mouseMap["mouse2"] = SDL_BUTTON_MIDDLE; // Middle
	}
}

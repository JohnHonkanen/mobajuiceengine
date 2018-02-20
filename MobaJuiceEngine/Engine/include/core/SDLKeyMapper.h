#pragma once
#include <map>
#include <string>
#include <SDL.h>

using namespace std;
namespace Engine {
	void InitKeyMap(map<string, Uint8> &keyMap, map<string, int> &mouseMap) {
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
		keyMap["1"] = 30;
		keyMap["2"] = 31;
		keyMap["3"] = 32;
		keyMap["4"] = 33;
		keyMap["5"] = 34;
		keyMap["6"] = 35;
		keyMap["7"] = 36;
		keyMap["8"] = 37;
		keyMap["9"] = 38;
		keyMap["0"] = 39;

		mouseMap["mouse0"] = 0; // Left
		mouseMap["mouse1"] = 0; // Right
		mouseMap["mouse2"] = 0; // Middle
	}
}

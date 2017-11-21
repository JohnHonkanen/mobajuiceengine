#pragma once

#include <SDL.h>

namespace Engine {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void Update(bool &running);
		void GetMousePos(int &x, int &y);
	private:

		int mouseX, mouseY;
	};
}
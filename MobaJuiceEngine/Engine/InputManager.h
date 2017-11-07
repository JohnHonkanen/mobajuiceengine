#pragma once

#include <SDL.h>
namespace Engine {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void Update();
		void GetMousePos(int &x, int &y);
	private:

		int mouseX, mouseY;
	};
}
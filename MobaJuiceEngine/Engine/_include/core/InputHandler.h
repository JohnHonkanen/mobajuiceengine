#pragma once

#include <SDL.h>
#include <map>

namespace Engine {
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void Update(bool &running);

	};

}

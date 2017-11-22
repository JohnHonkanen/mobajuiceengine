#include "InputHandler.h"
#include <iostream>

using namespace std;

namespace Engine {
	InputHandler::InputHandler()
	{
	}


	InputHandler::~InputHandler()
	{
	}

	//void InputHandler::Update(bool & running)
	//{

	//	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	//	SDL_Event sdlEvent; 

	//	while (SDL_PollEvent(&sdlEvent)) {
	//		if (sdlEvent.type == SDL_QUIT) {
	//			running = false;
	//		}

	//		if (sdlEvent.type == SDL_KEYDOWN) {
	//			switch (sdlEvent.key.keysym.sym) {

	//				case SDLK_ESCAPE:
	//					cout << "Program exit" << endl;
	//					break;
	//				case SDLK_a:
	//					cout << "A pressed" << endl;
	//					break;

	//				default:
	//					cout << "Default called" << endl;
	//					break;
	//			}
	//		}
	//	}
	//}
}

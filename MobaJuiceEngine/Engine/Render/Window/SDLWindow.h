/*
	Manages the window and provides a facade to the SDL library
	Dev: John Honkanen (B00291253)
*/
#pragma once
#include "Window.h"
#include <GL\glew.h>
#include <SDL.h>
#include <string>

class SDLWindow : public Window {
public:
	// Intializes the SDLWindow, with window name and resolution size.
	SDLWindow(const std::string windowName, unsigned int width,  unsigned int height);
	virtual ~SDLWindow();
	//Initialize and set up the SDL library
	void Initialize();
	//Swap buffers using SDL
	void SwapBuffers();
	//Destory SDL instance and window
	void Destroy();
private:
	//Create SDL GL Context and assigns it.
	void SetupRC(SDL_GLContext &context);

	unsigned int width;
	unsigned int height;
	std::string windowName;

	SDL_Window *window;
	SDL_GLContext glContext;
};
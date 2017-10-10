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
	SDLWindow(const std::string windowName, unsigned int width,  unsigned int height);
	virtual ~SDLWindow();
	void Initialize();
	void SwapBuffers();
	void Destroy();
private:
	void SetupRC(SDL_GLContext &context);

	unsigned int width;
	unsigned int height;
	std::string windowName;

	SDL_Window *window;
	SDL_GLContext glContext;
};
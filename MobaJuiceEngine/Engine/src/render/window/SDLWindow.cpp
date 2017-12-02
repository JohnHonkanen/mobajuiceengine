#include "render/window/SDLWindow.h"
#include <SDL.h>
#include <iostream>
namespace Engine {

	/*
		Intializes the SDLWindow, with window name and resolution size.
		@param windowName	Name of the window
		@param width		width of the window
		@param height		height of the window
	*/
	SDLWindow::SDLWindow(const std::string windowName, unsigned int width, unsigned int height)
	{
		SDLWindow::windowName = windowName;
		SDLWindow::width = width;
		SDLWindow::height = height;

	}

	SDLWindow::~SDLWindow()
	{
	}

	/*
		Initializes and setups the render scene
	*/
	void SDLWindow::Initialize()
	{
		SetupRC(SDLWindow::glContext);
		SDL_ShowCursor(SDL_DISABLE);
	}
	/*
		Calls the SDL swap buffers
	*/
	void SDLWindow::SwapBuffers()
	{
		SDL_GL_SwapWindow(window);
	}
	/*
		Delete the current context and window. Ask SDL to quit and close the application window
	*/
	void SDLWindow::Destroy()
	{
		SDL_GL_DeleteContext(SDLWindow::glContext);
		SDL_DestroyWindow(SDLWindow::window);
		SDL_Quit();
	}
		SDL_Window * SDLWindow::GetWindow()
		{
			return window;
		}
	/*
		Setups the Render Scene using OpenGL 3.3.
		@param context		OpenGL window context
	*/
	void SDLWindow::SetupRC(SDL_GLContext & context)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0) { // Initialize video
			std::cout << "Unable to initailize SDL" << " ";
			exit(1);
		}
		// Request an OpenGL 3.0 context.
		// Not able to use SDL to choose profile (yet), should default to core profile on 3.2 or later
		// If you request a context not supported by your drivers, no OpenGL context will be created

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // Turn on x4 multisampling anti-aliasing (MSAA)

														   // Create 800x600 window
		window = SDL_CreateWindow(SDLWindow::windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SDLWindow::width, SDLWindow::height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (!window) {
			std::cout << "Unable to create window" << " ";
			exit(1);
		}

		context = SDL_GL_CreateContext(window); // Create opengl context and attach to window
		SDL_GL_SetSwapInterval(1); // set swap buffers to sync with monitor's vertical refresh rate
	}
}
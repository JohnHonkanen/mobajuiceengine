/*
	OpenGL Graphics Handler Facade.
	Dev: John Honkanen (B00291253)
*/
#pragma once
#include <memory>
#include "GraphicHandler.h"
#include "../Window/Window.h"
namespace Engine {
	class OGLGraphicHandler : public GraphicHandler {
	public:
		//Initializes an instance of the OGLGraphicsHandlers, with a Window being used
		OGLGraphicHandler(Window * window);
		virtual ~OGLGraphicHandler();
		//Sets up and Initializes OpenGL
		void Initialize();
		//Calls Start of the Render Loop, and Clears the Screen
		void Start();
		//Calls the Swapbuffer of the Window
		void End();
		//Deallocate the Window Memory
		void Destroy();
	private:
		std::unique_ptr<Window> window;

	};
}
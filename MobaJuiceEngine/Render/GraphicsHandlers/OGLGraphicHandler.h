/*
	OpenGL Graphics Handler Facade.
	Dev: John Honkanen (B00291253)
*/
#pragma once
#include <memory>
#include "GraphicHandler.h"
#include "../Window/Window.h"
class OGLGraphicHandler : public GraphicHandler {
private:
	std::unique_ptr<Window> window;
public:
	OGLGraphicHandler(Window * window);
	virtual ~OGLGraphicHandler();
	void Initialize();
	void Start();
	void End();
	void Destroy();

};
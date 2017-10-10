#include "OGLGraphicHandler.h"
#include <GL\glew.h>
OGLGraphicHandler::OGLGraphicHandler(Window *window)
{
	OGLGraphicHandler::window = std::unique_ptr<Window>(window);
}

OGLGraphicHandler::~OGLGraphicHandler()
{
}

void OGLGraphicHandler::Initialize()
{
	window->Initialize();

	// Set this to true so GLEW knows to use a modern approach to retreiving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Setup OpenGL options
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST); // Enable Z Buffer
	glEnable(GL_BLEND); // Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OGLGraphicHandler::Start()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Color to clear with (Background color of active scene)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
}

void OGLGraphicHandler::End()
{
	// Swap the buffers (Update Scene)
	window->SwapBuffers();
}

void OGLGraphicHandler::Destroy()
{
	window->Destroy();
}

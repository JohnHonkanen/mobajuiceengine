#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include <iostream>
#include <memory>
#include "Render\GraphicsHandlers\OGLGraphicHandler.h"
#include "Render\Window\SDLWindow.h"
using namespace std;


int main(int argc, char *argv[]){

	OGLGraphicHandler graphicsHandler(new SDLWindow("MobaJuice", 800, 800));
	graphicsHandler.Initialize();

	//Loop for Graphics
	graphicsHandler.Start();
	//Any draw calls goes here
	graphicsHandler.End();

	graphicsHandler.Destroy();
	return 0;
}
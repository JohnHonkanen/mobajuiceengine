#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include "Engine\GameEngine.h"

using namespace Engine;

int main(int argc, char *argv[]){

	GameEngine engine;
	engine.Load("default_scene.xml");

	engine.Run();

	return 0;
}
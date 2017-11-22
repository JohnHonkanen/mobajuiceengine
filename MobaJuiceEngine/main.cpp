#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include "Engine\GameEngine.h"
#include "Engine\MobaJuiceCore.h"

using namespace Engine;

int main(int argc, char *argv[]){

	GameEngine engine;
	engine.Load("BaseScene.xml");
	Scene *scene = engine.GetActiveScene();
	GameObjectManager *list = scene->GetGameObjectManager();

	GameObject *camera = list->Find("Camera_1");
	camera->transform->Translate(vec3(0.0f, 0.0f, -15.0f));
	engine.Run();

	return 0;
}
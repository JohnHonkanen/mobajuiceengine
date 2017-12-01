#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include "Engine\GameEngine.h"
#include "Engine\MobaJuiceCore.h"
#include "Engine\InputManager.h"
#include <iostream>
using namespace Engine;

int main(int argc, char *argv[]){

	GameEngine engine;

	engine.LoadSettings("default-settings.xml");
	engine.Load("BaseScene.xml");


	Scene *scene = engine.GetActiveScene();
	GameObjectManager *list = scene->GetGameObjectManager();

	GameObject *camera = list->Find("Camera_1");
	camera->transform->Translate(vec3(0.0f, 20.0f, -45.0f));
	camera->transform->SetEulerAngle(vec3(45.0f, 0.0f, 0.0f));

	FreeCameraControl::Create(camera);

	GameObject *boletus = list->LoadPrefab("mushroom.xml");


	engine.Run();


	return 0;
}
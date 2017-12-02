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
	/*GameEngine::manager.inputManager.AddKey("Horizontal", "d", "a");
	GameEngine::manager.inputManager.AddKey("Vertical", "w", "s");
	GameEngine::manager.inputManager.AddKey("FreezeMouse", "f", "g");*/

	engine.LoadSettings("default-settings.xml");
	engine.Load("BaseScene.xml");


	Scene *scene = engine.GetActiveScene();
	GameObjectManager *list = scene->GetGameObjectManager();

	GameObject *terrain = list->CreateGameObject("Terrain");
	Terrain * t = Terrain::Create(terrain, 10, 150, 150, 0.0003f, 1.0f, "terrainShader");
	t->material.diffuseMap = "Assets/Textures/ground.jpg";

	GameObject *camera = list->Find("Camera_1");
	camera->transform->Translate(vec3(0.0f, 20.0f, -45.0f));
	camera->transform->SetEulerAngle(vec3(45.0f, 0.0f, 0.0f));

	FreeCameraControl::Create(camera);

	//GameObject *boletus = list->LoadPrefab("mushroom.xml");


	engine.Run();
	engine.Save("Mushroom_Scene.xml");


	return 0;
}
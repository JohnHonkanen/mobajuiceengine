#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include "core\GameEngine.h"
#include "MobaJuiceCore.h"
#include "core\InputManager.h"
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
	scene->AddSkyBox("Assets/Skybox/Nebula/Nebula.tga");
	GameObjectManager *list = scene->GetGameObjectManager();

	GameObject *terrain = list->CreateGameObject("Terrain");
	Terrain * t = Terrain::Create(terrain, 10, 150, 150, 0.003f, 10.0f, "terrainShader");
	t->material.diffuseMap = "Assets/Textures/ground.jpg";

	GameObject *camera = list->Find("Camera_1");
	camera->transform->Translate(vec3(0.0f, 20.0f, -45.0f));
	camera->transform->SetEulerAngle(vec3(45.0f, 0.0f, 0.0f));

	FreeCameraControl::Create(camera);

	GameObject *boletus = list->LoadPrefab("mushroom.xml");
	boletus->transform->SetPosition(10, t->GetHeight(10,10), 10);
	boletus->transform->SetScale(vec3(0.05f));


	engine.Run();
	engine.Save("Mushroom_Scene.xml");


	return 0;
}
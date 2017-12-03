#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include "core\GameEngine.h"
#include "MobaJuiceCore.h"
#include "core\InputManager.h"
#include "components\TextureSetter.h"
#include <iostream>
using namespace Engine;

int main(int argc, char *argv[]){

	GameEngine engine = GameEngine();
	/*GameEngine::manager.inputManager.AddKey("Horizontal", "d", "a");
	GameEngine::manager.inputManager.AddKey("Vertical", "w", "s");
	GameEngine::manager.inputManager.AddKey("FreezeMouse", "f", "g");*/

	engine.LoadSettings("default-settings.xml");
	//engine.Load("BaseScene.xml");

	Scene *scene = engine.CreateScene("Demo Scene");
	scene->AddSkyBox("Assets/Skybox/Nebula/Nebula.tga");
	GameObjectManager *list = scene->GetGameObjectManager();

	GameObject *terrain = list->CreateGameObject("Terrain");
	Terrain * t = Terrain::Create(terrain, 10, 20, 20, 0.003f, 10.0f, "terrainShader");
	t->material.diffuseMap = "Assets/Textures/ground.jpg";

	GameObject *camera = list->CreateGameObject("Camera");
	Camera *c = Camera::Create(camera);
	c->SetFarClippingPlane(1000);
	camera->transform->Translate(vec3(0.0f, 20.0f, -45.0f));
	camera->transform->SetEulerAngle(vec3(45.0f, 0.0f, 0.0f));

	FreeCameraControl *fcc = FreeCameraControl::Create(camera);

	GameObject *boletus = list->LoadPrefab("mushroom.xml");
	boletus->transform->SetPosition(30, t->GetHeight(30,50), 50);
	boletus->transform->SetScale(vec3(0.05f));
	boletus->transform->SetEulerAngle(vec3(-90.0f,0.0f,0.0f));

	GameObject *rock = list->CreateGameObject("rock");
	MeshRenderer::Create(rock, "Assets/Models/rock/Rock.obj");
	TextureSetter::Create(rock, "Assets/Textures/Rock/Rock_d.jpg");
	rock->transform->SetScale(vec3(0.3f));
	rock->transform->Rotate(vec3(-60, 0, 0));
	rock->transform->SetPosition(-10, t->GetHeight(-10, 20), 20);

	rock = list->CreateGameObject("rock");
	MeshRenderer::Create(rock, "Assets/Models/rock/Rock.obj");
	TextureSetter::Create(rock, "Assets/Textures/Rock/Rock_d.jpg");
	rock->transform->SetScale(vec3(0.2f));
	rock->transform->Rotate(vec3(0, 0, 0));
	rock->transform->SetPosition(30, t->GetHeight(30, -5), -30);


	engine.Run();
	//engine.Save("Mushroom_Scene.xml");


	return 0;
}
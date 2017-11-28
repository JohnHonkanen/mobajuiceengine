#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include "Engine\GameEngine.h"
#include "Engine\MobaJuiceCore.h"
#include "Engine\InputManager.h"
#include "Engine\Component\Text2D.h"
#include <iostream>
using namespace Engine;

int main(int argc, char *argv[]){
	std::cout << "Choose a Save: 1), 2) 3= quit" << std::endl;
	int save = 0;
	std::cin >> save;
	if (save == 3)
		return 0;

	GameEngine engine;
	engine.Load("BaseScene.xml");
	//engine.Load("mush.xml");
	if (save == 1) {
		
		engine.Run();
	}
	else {

		Scene *scene = engine.GetActiveScene();
		GameObjectManager *list = scene->GetGameObjectManager();

		GameObject *camera = list->Find("Camera_1");
		camera->transform->Translate(vec3(0.0f, 20.0f, -45.0f));
		camera->transform->SetEulerAngle(vec3(45.0f, 0.0f, 0.0f));

		FreeCameraControl::Create(camera);

		GameObject *boletus = list->CreateGameObject("mushroom");
		MeshRenderer::Create(boletus, "Assets/Models/boletus/boletus.dae");
		boletus->transform->Translate(vec3(30,0, 30.0f));
		boletus->transform->SetEulerAngle(vec3(-90.0f, 0.0f, -30.0f));
		boletus->transform->SetScale(vec3(0.5f));

		GameObject *boletus2 = list->CreateGameObject("mushroom2");
		MeshRenderer::Create(boletus2, "Assets/Models/boletus/boletus.dae");
		boletus2->transform->Translate(vec3(-30, 0, 50.0f));
		boletus2->transform->SetEulerAngle(vec3(-90.0f, 0.0f, 10.0f));
		boletus2->transform->SetScale(vec3(0.5f));

		GameObject *text = list->CreateGameObject("testText");
		Text2D::Create(text, "text2D", "Hello", { 255,255,0 }, "Assets/Fonts/MavenPro-Regular.ttf");
		text->transform->Translate(vec3(640.0f, 360.0f, 10.0f));
		text->transform->SetScale(vec3(20.0f, 10.0f, 0.0f));

		engine.Run();
	}

	
	
	
	
	

	return 0;
}
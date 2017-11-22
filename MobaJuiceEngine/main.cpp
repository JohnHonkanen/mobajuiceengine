#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#define DEG_TO_RAD 0.017453293

#include <iostream>
#include <memory>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Engine\Physics\RayCast.h"
#include "Engine\InputManager.h"
#include "Engine\Physics\RaycastUtility.h"

#include "Engine\Render\GraphicsHandlers\OGLGraphicHandler.h"
#include "Engine\Render\Window\SDLWindow.h"
#include "Engine\Render\Mesh\OGLMeshManager.h"
#include "Engine\Render\ShaderManager.h"
#include "Engine\GameObject.h"
#include "Engine\GameObjectManager.h"
#include "Engine\Component\Camera.h"
#include "Engine\Component\MeshRenderer.h"
#include "Engine\Scene.h"
#include "Engine\GameEngine.h"

using namespace std;
using namespace glm;
using namespace Engine;

int main(int argc, char *argv[]){

	std::string path = "Assets/Models/arissa/Arissa.dae";
	std::string path2 = "Assets/Models/boletus/boletus.dae";
	std::string path3 = "Assets/Crate/deer.dae";
	std::string path4 = "Assets/Crate/deer.dae";

	GameEngine engine;
	//engine.Load("default_scene.xml");
	//Scene * scene = engine.CreateScene();
	//GameObjectManager *gameObjects = scene->GetGameObjectManager();
	//GameObject * cameraWrapper = gameObjects->createGameObject("Camera");
	//Camera::Create(cameraWrapper);
	//Camera::mainCamera->SetFarClippingPlane(1000.0f);

	//cameraWrapper->transform->SetPosition(vec3(0.0f, 75.0f, 0.0f));
	//cameraWrapper->transform->SetEulerAngle(vec3(45.0f, 0.0f, 0.0f));

	//GameObject *deer = gameObjects->createGameObject("deer");
	////Create and attaches it the arissa (deer)
	//MeshRenderer::Create(deer, path);

	//GameObject *arissa = gameObjects->createGameObject("arissa");
	////Create and attaches it the arissa (deer)
	//MeshRenderer::Create(arissa, path3);
	//arissa->transform->SetScale(vec3(0.02f));
	//arissa->transform->SetPosition(vec3(20.0f, 0.0f, 60.0f));
	//arissa->transform->SetEulerAngle(vec3(-90.0f, 0.0f,0.0f));

	//deer->transform->SetPosition(glm::vec3(-0.0f, -0.0f, 80.0f));
	//deer->transform->SetScale(glm::vec3(0.1f));

	//GameObject *boletus = gameObjects->createGameObject("Boletus");
	//MeshRenderer::Create(boletus, path2);
	//boletus->transform->SetEulerAngle(vec3(-90.0f, 0,0));
	//boletus->transform->SetScale(vec3(0.25f));

	engine.Run();

	engine.Save();
	graphicsHandler.Destroy();
	return 0;
}
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

	OGLGraphicHandler graphicsHandler(new SDLWindow("MobaJuice", 1280, 720));
	graphicsHandler.Initialize();

	ShaderManager shaderManager;
	
	OGLShader *baseProgram = shaderManager.CreateShader("phong", "Assets/Shaders/textured.vert", "Assets/Shaders/textured.frag");

	std::string path = "Assets/Models/arissa/Arissa.dae";
	std::string path2 = "Assets/Models/boletus/boletus.dae";
	std::string path3 = "Assets/Crate/deer.dae";
	TextureManager texureManager;
	OGLMeshManager meshManager;
	InputManager inputManager;
	meshManager.SetShaderProgram("phong", &shaderManager);
	meshManager.SetTextureManager(&texureManager);
	GameEngine engine;
	Scene * scene = engine.CreateScene();
	GameObjectManager *gameObjects = scene->GetGameObjectManager();
	GameObject * cameraWrapper = gameObjects->createGameObject("Camera");
	Camera::Create(cameraWrapper);
	Camera::mainCamera->SetFarClippingPlane(1000.0f);

	cameraWrapper->transform->SetPosition(vec3(0.0f, 75.0f, 0.0f));
	cameraWrapper->transform->SetEulerAngle(vec3(45.0f, 0.0f, 0.0f));

	GameObject *deer = gameObjects->createGameObject("deer");
	//Create and attaches it the arissa (deer)
	MeshRenderer::Create(deer, path, &meshManager);

	GameObject *arissa = gameObjects->createGameObject("arissa");
	//Create and attaches it the arissa (deer)
	MeshRenderer::Create(arissa, path3, &meshManager);
	arissa->transform->SetScale(vec3(0.02f));
	arissa->transform->SetPosition(vec3(20.0f, 0.0f, 60.0f));
	arissa->transform->SetEulerAngle(vec3(-90.0f, 0.0f,0.0f));

	deer->transform->SetPosition(glm::vec3(-0.0f, -0.0f, 80.0f));
	deer->transform->SetScale(glm::vec3(0.1f));

	GameObject *boletus = gameObjects->createGameObject("Boletus");
	MeshRenderer::Create(boletus, path2, &meshManager);
	boletus->transform->SetEulerAngle(vec3(-90.0f, 0,0));
	boletus->transform->SetScale(vec3(0.25f));

	int mousePositionX, mousePositionY;
	glm::vec3 mousePos3D = vec3(0);
	RayCast raycaster(mousePos3D);

	float r = -10.0f;
	float rd = 0.0f;
	float rv = 0.1f;
	SDL_Event sdlEvent;  // variable to detect SDL events
	bool running = true; // set running to true
	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT) {
				running = false;
			}
			// Input loop
			inputManager.Update();
			inputManager.GetMousePos(mousePositionX, mousePositionY);
			glm::vec3 rayNormalizedDevSpace = RaycastUtility::ConvertPointToNormalizeCoords(mousePositionX, mousePositionY, 1280, 720);
			vec4 rayDirection = RaycastUtility::ConvertNormalizedCoordsToWorldCoords(rayNormalizedDevSpace, Camera::mainCamera->GetProjectionMatrix(), Camera::mainCamera->GetViewMatrix());
			glm::vec3 cameraPosition = Camera::mainCamera->transform->GetPosition();
			float steps = glm::abs(cameraPosition.y / rayDirection.y);
			mousePos3D = cameraPosition + glm::vec3(rayDirection * steps);

			cout << mousePos3D.x << " ,  " << mousePos3D.y << " ,  " << mousePos3D.z << endl;

		}
		scene->Update();
		vec3 dir = normalize(mousePos3D - boletus->transform->GetPosition());
		boletus->transform->Translate(dir);
		deer->transform->Rotate(vec3(0.0f, 1.0f, 0.0f));
		//Loop for Graphics
		graphicsHandler.Start();
		scene->Draw();
		
		graphicsHandler.End();
	}
	graphicsHandler.Destroy();
	return 0;
}
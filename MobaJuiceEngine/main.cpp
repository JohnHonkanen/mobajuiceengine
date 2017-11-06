#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#define DEG_TO_RAD 0.017453293

#include <iostream>
#include <memory>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Engine\Render\GraphicsHandlers\OGLGraphicHandler.h"
#include "Engine\Render\Window\SDLWindow.h"
#include "Engine\Render\Mesh\OGLMeshManager.h"
#include "Engine\Render\ShaderManager.h"
#include "Engine\GameObject.h"
#include "Engine\GameObjectManager.h"
#include "Engine\Component\Camera.h"
#include "Engine\Component\MeshRenderer.h"
using namespace std;
using namespace glm;
using namespace Engine;

int main(int argc, char *argv[]){

	OGLGraphicHandler graphicsHandler(new SDLWindow("MobaJuice", 1280, 720));
	graphicsHandler.Initialize();

	ShaderManager shaderManager;
	
	OGLShader *baseProgram = shaderManager.CreateShader("phong", "Assets/Shaders/textured.vert", "Assets/Shaders/textured.frag");

	std::string path = "Assets/Models/arissa/Arissa.dae";
	//std::string path = "Assets/Crate/deer.dae";
	TextureManager texureManager;
	OGLMeshManager meshManager;
	meshManager.SetShaderProgram("phong", &shaderManager);
	meshManager.SetTextureManager(&texureManager);

	GameObjectManager gameObjects;
	GameObject * cameraWrapper = gameObjects.createGameObject("Camera");
	Camera::Create(cameraWrapper);

	cameraWrapper->transform->SetPosition(vec3(0.0f, 2.0f, 0.0f));
	cameraWrapper->transform->SetEulerAngle(vec3(0.0f, 0.0f, 0.0f));

	GameObject *deer = gameObjects.createGameObject("deer");
	//Create and attaches it the arissa (deer)
	MeshRenderer::Create(deer, path, &meshManager);

	deer->transform->SetPosition(glm::vec3(-0.0f, -3.0, 40.0f));
	deer->transform->SetScale(glm::vec3(0.05f));


	vec3 pos;

	float r = -10.0f;
	float rd = 0.0f;
	float rv = 0.1f;
	SDL_Event sdlEvent;  // variable to detect SDL events
	bool running = true; // set running to true
	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT)
				running = false;
		}
		if (r < -20.0f || r > 20.0f) {
			rv = -rv;
		}
		r += rv;
		rd += 1.0f;
		gameObjects.Update();

		deer->transform->SetEulerAngle(vec3(0.0f, rd, 0.0f));
		//Loop for Graphics
		graphicsHandler.Start();
		gameObjects.Draw();
		
		graphicsHandler.End();
	}
	graphicsHandler.Destroy();
	return 0;
}
#include "GameEngine.h"

#include <cereal/archives/xml.hpp>
#include <cereal\types\memory.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "Scene.h"

#include "Render\GraphicsHandlers\OGLGraphicHandler.h"
#include "Render\Window\SDLWindow.h"

namespace Engine {

	ManagerCollection GameEngine::manager = ManagerCollection();

	Scene * GameEngine::CreateScene()
	{
		activeScene = std::make_unique<Scene>();
		return activeScene.get();
	}

	void GameEngine::Save()
	{
		Save("default_scene.xml");
	}

	void GameEngine::Save(const char * scene)
	{
		std::ofstream os(scene);
		cereal::XMLOutputArchive oArchive(os);
		oArchive(activeScene);
	}

	void GameEngine::Load(const char * scene)
	{
		std::ifstream is(scene);
		cereal::XMLInputArchive iArchive(is);
		iArchive(activeScene);
	}

	void GameEngine::Initialize()
	{
		manager.shaderManager.CreateShader("phong", "Assets/Shaders/textured.vert", "Assets/Shaders/textured.frag");
		manager.meshManager.SetShaderProgram("phong", &manager.shaderManager);
		manager.meshManager.SetTextureManager(&manager.textureManager);

		activeScene->OnLoad();
	}

	void GameEngine::Run()
	{
		OGLGraphicHandler graphicsHandler(new SDLWindow("MobaJuice", 1280, 720));
		graphicsHandler.Initialize();
		Initialize();

		bool running = true;
		SDL_Event e;
		while (running) {

			//Input Poll
			manager.inputManager.Update(running);

			activeScene->Update();

			graphicsHandler.Start();
			activeScene->Draw();

			graphicsHandler.End();
		}

		graphicsHandler.Destroy();
	}
}


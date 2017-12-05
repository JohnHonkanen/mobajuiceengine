#include "core/GameEngine.h"

#include <cereal/archives/xml.hpp>
#include <cereal\types\memory.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "core/Scene.h"

#include "render\graphics\OGLGraphicHandler.h"
#include "render\window\SDLWindow.h"

namespace Engine {

	ManagerCollection GameEngine::manager = ManagerCollection();

	GameEngine::GameEngine()
	{
		srand(time(NULL));
	}

	Scene * GameEngine::CreateScene(string name)
	{
		activeScene = std::make_unique<Scene>(name);
		return activeScene.get();
	}

	Scene * GameEngine::GetActiveScene()
	{
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

	void GameEngine::SaveSettings(const char * settings)
	{
		std::ofstream os(settings);
		cereal::XMLOutputArchive oArchive(os);
		oArchive(manager);
	}

	void GameEngine::LoadSettings(const char * settings)
	{
		std::ifstream is(settings);
		cereal::XMLInputArchive iArchive(is);
		iArchive(manager);
	}

	void GameEngine::Initialize()
	{
		manager.shaderManager.CreateShader("phong", "Assets/Shaders/textured.vert", "Assets/Shaders/textured.frag");
		manager.shaderManager.CreateShader("terrainShader", "Assets/Shaders/terrain.vert", "Assets/Shaders/terrain.frag");
		manager.shaderManager.CreateShader("skyBoxShader", "Assets/Shaders/skyBoxBasic.vert", "Assets/Shaders/skyBoxBasic.frag");
		manager.shaderManager.CreateShader("text2D", "Assets/Shaders/text2D.vert", "Assets/Shaders/text2D.frag");
		manager.meshManager.SetShaderProgram("phong", &manager.shaderManager);
		manager.meshManager.SetTextureManager(&manager.textureManager);

		activeScene->OnLoad();
	}

	void GameEngine::Run()
	{
		OGLGraphicHandler graphicsHandler(new SDLWindow("MobaJuice", 1280, 720));
		graphicsHandler.Initialize();
		Initialize();

		activeScene->Start();
		bool running = true;
		SDL_Event e;
		while (running) {

			frameStart = SDL_GetTicks();
			//Input Poll
			manager.inputManager.Update(running, graphicsHandler.GetWindow());

			activeScene->Input();
			activeScene->Update();

			graphicsHandler.Start();
			activeScene->Draw();

			graphicsHandler.End();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}
		}

		graphicsHandler.Destroy();
	}
}


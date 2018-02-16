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
	GameEngine::Paths GameEngine::path = GameEngine::Paths();
	vec2 GameEngine::screenSize = vec2(1280, 720);
	bool GameEngine::DEBUG = false;

	GameEngine::GameEngine() : GameEngine(false)
	{	
	}

	GameEngine::GameEngine(bool debug)
	{
		DEBUG = debug;
		srand(time(NULL));

		//Create Default Paths
		path.assetPath = "../GameEngine/MobaJuiceEngine/Engine/assets/";
		path.shaderPath = "../GameEngine/MobaJuiceEngine/Engine/shaders/";
		path.settingPath = "../GameEngine/MobaJuiceEngine/Engine/settings/";
		path.enginePath = "../GameEngine/";
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
		manager.gameObjectManager = activeScene->GetGameObjectManager();
		//Set default Engine Shaders
		manager.shaderManager.CreateShader("phong", string(path.shaderPath + "textured.vert").c_str(), string(path.shaderPath + "textured.frag").c_str());
		manager.shaderManager.CreateShader("terrainShader", string(path.shaderPath + "terrain.vert").c_str(), string(path.shaderPath + "terrain.frag").c_str());
		manager.shaderManager.CreateShader("terrainGridShader", string(path.shaderPath + "terrainGrid.vert").c_str(), string(path.shaderPath + "terrainGrid.frag").c_str());
		manager.shaderManager.CreateShader("skyBoxShader", string(path.shaderPath + "skyBoxBasic.vert").c_str(), string(path.shaderPath + "skyBoxBasic.frag").c_str());
		manager.shaderManager.CreateShader("text", string(path.shaderPath + "text2D.vert").c_str(), string(path.shaderPath + "text2D.frag").c_str());
		manager.shaderManager.CreateShader("defaultHUDShader", string(path.shaderPath + "defaultHUD.vert").c_str(), string(path.shaderPath + "defaultHUD.frag").c_str());
		manager.meshManager.SetShaderProgram("phong", &manager.shaderManager);
		manager.meshManager.SetTextureManager(&manager.textureManager);

		//Mouse keybind for the event system
		manager.inputManager.AddKey("mouse0", "mouse0"); //Left
		manager.inputManager.AddKey("mouse1", "mouse1"); //Right

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
			//Event Poll
			manager.eventManager.Update();
			//Input Poll
			manager.inputManager.Update(running, graphicsHandler.GetWindow());

			activeScene->Input();
			activeScene->Update(frameTime);

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

	void GameEngine::SetDefaultPath(Paths::PATH_TYPE type, string p)
	{
		switch (type) {
		case Paths::PATH_TYPE::ASSET:
			path.assetPath = p;
			break;
		case Paths::PATH_TYPE::SHADER:
			path.shaderPath = p;
			break;
		case Paths::PATH_TYPE::SETTINGS:
			path.settingPath = p;
			break;
		case Paths::PATH_TYPE::ENGINE:
			path.enginePath = p;
			break;
		default:
			//To DO Add error code.
			break;
		}
	}

	string GameEngine::GetPath(Paths::PATH_TYPE type) const
	{
		switch (type) {
		case Paths::PATH_TYPE::ASSET:
			return path.assetPath;
		case Paths::PATH_TYPE::SHADER:
			return path.shaderPath;
		case Paths::PATH_TYPE::SETTINGS:
			return path.settingPath;
		case Paths::PATH_TYPE::ENGINE:
			return path.enginePath;
		default:
			return nullptr;
		}
	}
}


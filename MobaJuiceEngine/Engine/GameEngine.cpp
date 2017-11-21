#include "GameEngine.h"

#include <cereal/archives/xml.hpp>
#include <cereal\types\memory.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "Scene.h"
namespace Engine {
	Scene * GameEngine::CreateScene()
	{
		activeScene = std::make_unique<Scene>();
		return activeScene.get();
	}

	void GameEngine::Save()
	{
		Save("default_scene");
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

	void GameEngine::Run()
	{
	}
}


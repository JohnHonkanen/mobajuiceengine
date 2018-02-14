#include "core/GameObjectManager.h"
#include <cereal/archives/xml.hpp>
#include <cereal\types\memory.hpp>
#include <iostream>
#include <fstream>
namespace Engine {
	GameObjectManager::GameObjectManager()
	{
	}

	GameObjectManager::~GameObjectManager()
	{
	}

	void GameObjectManager::OnLoad()
	{
		for (auto const &gameobjectPair : gameObjects) {
			gameobjectPair.second->OnLoad();
		}
	}

	void GameObjectManager::Start()
	{
		for (auto const &gameobjectPair : gameObjects) {
			gameobjectPair.second->Start();
		}
	}

	void GameObjectManager::Input()
	{
		for (auto const &gameobjectPair : gameObjects) {
			gameobjectPair.second->Input();
		}
	}

	void GameObjectManager::Update(double dt)
	{
		for (auto const &gameobjectPair : gameObjects) {
			gameobjectPair.second->Update(dt);
		}
	}

	void GameObjectManager::Draw()
	{
		for (auto const &gameobjectPair : gameObjects) {
			gameobjectPair.second->Draw();
		}
	}

	void GameObjectManager::RegisterGameObject(GameObject * gameObject)
	{
		if (gameObject->name == "") {
			int count = gameObjects.size();
			gameObject->name = "GameObject" + count;
		}
		//If already exist
		if (counter.count(gameObject->name) > 0) {
			string name = gameObject->name;
			gameObject->name = name + "_" + std::to_string(counter[name]);
			counter[name]++;
		}
		else {
			counter[gameObject->name] = 1;
		}
		

		gameObjects.insert(std::pair<std::string, GameObjUniqPtr>(gameObject->name, GameObjUniqPtr(gameObject)));
	}

	GameObject * GameObjectManager::DeregisterGameObject(std::string name)
	{
		GameObject * gameObject = Find(name);
		gameObjects[name].release();
		gameObjects.erase(name);
		return gameObject;
	}

	GameObject * GameObjectManager::CreateGameObject(std::string name)
	{
		GameObject *object = new GameObject(name);
		RegisterGameObject(object);

		return object;
	}

	GameObject * GameObjectManager::Find(std::string name)
	{
		if (gameObjects.find(name) == gameObjects.end())
			return nullptr;

		return gameObjects[name].get();
	}
	GameObject * GameObjectManager::LoadPrefab(const char * prefab)
	{
		GameObjUniqPtr gameObject;

		std::ifstream is(prefab);
		cereal::XMLInputArchive iArchive(is);
		iArchive(gameObject);

		GameObject * obj = gameObject.get();
		gameObject.release();
		RegisterGameObject(obj);

		return obj;

	}

	bool GameObjectManager::SavePrefab(const char * prefab, std::string name)
	{
		if (gameObjects.find(name) == gameObjects.end())
			return false;

		std::ofstream os(prefab);
		cereal::XMLOutputArchive oArchive(os);
		oArchive(gameObjects[name]);

		return true;
	}
}

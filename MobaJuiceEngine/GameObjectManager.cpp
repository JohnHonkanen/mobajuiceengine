#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Update()
{
	for (auto const &gameobjectPair : gameObjects) {
		gameobjectPair.second->Update();
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

	gameObjects.insert(std::pair<std::string, GameObjUniqPtr>(gameObject->name, GameObjUniqPtr(gameObject)));
}

void GameObjectManager::DeregisterGameObject(std::string name)
{
	gameObjects.erase(name);
}

GameObject * GameObjectManager::Find(std::string name)
{
	if (gameObjects.find(name) == gameObjects.end())
		return nullptr;

	return gameObjects[name].get();
}

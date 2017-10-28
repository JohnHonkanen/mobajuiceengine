#pragma once
#include <memory>
#include <map>
#include "GameObject.h"
namespace Engine {
	typedef std::unique_ptr<GameObject> GameObjUniqPtr;

	class GameObjectManager
	{
	public:
		GameObjectManager();
		~GameObjectManager();

		void Update();
		void Draw();

		void RegisterGameObject(GameObject * gameObject);
		void DeregisterGameObject(std::string name);

		GameObject * Find(std::string name);

	private:
		std::map<std::string, GameObjUniqPtr> gameObjects;
	};
}
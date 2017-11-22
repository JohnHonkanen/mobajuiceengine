#pragma once
#include <string>
#include <memory>
#include <cereal\cereal.hpp>

#include "GameObjectManager.h"


using namespace std;
namespace Engine {
	class Scene {
	private:
		string name;
		unique_ptr<GameObjectManager> gameObjects;

	public:
		Scene();
		Scene(string name);
		~Scene();
		GameObjectManager * GetGameObjectManager();

		void OnLoad();
		void Start();
		void Input();
		void Update();
		void Draw();

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(name), CEREAL_NVP(gameObjects));
		}

	};
};
#pragma once
#include <string>
#include <memory>
#include <cereal\cereal.hpp>


using namespace std;
namespace Engine {
	class GameObjectManager;
	class Scene {
	private:
		string name;
		unique_ptr<GameObjectManager> gameObjects;

	public:
		Scene();
		Scene(string name);
		~Scene();
		GameObjectManager * GetGameObjectManager();

		void Start();
		void Update();
		void Draw();

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(name), CEREAL_NVP(gameObjects));
		}

	};
};
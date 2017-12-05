#pragma once
#include <string>
#include <memory>
#include <cereal\cereal.hpp>
#include "GameObjectManager.h"
#include "render\mesh\Skybox.h"

using namespace std;
namespace Engine {
	class Scene {
	private:
		string name;
		unique_ptr<GameObjectManager> gameObjects;
		Skybox skybox;
		bool hasSkyBox;
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

		void AddSkyBox(string skyBoxDirectory);

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(name), CEREAL_NVP(gameObjects));
		}

	};
};
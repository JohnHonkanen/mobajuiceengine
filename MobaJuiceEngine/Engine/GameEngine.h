#pragma once
#include <memory>
#include "ManagerCollection.h"
#include "Scene.h"
using namespace std;
namespace Engine {
	class GameEngine {
	public:
		Scene * CreateScene(string name);
		Scene * GetActiveScene();
		void Save();
		void Save(const char *scene);
		void Load(const char *scene);
		void Initialize();

		void Run();

		static ManagerCollection manager;
	private:
		std::unique_ptr<Scene> activeScene;
	};
}
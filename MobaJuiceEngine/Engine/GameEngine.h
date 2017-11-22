#pragma once
#include <memory>
#include "ManagerCollection.h"
using namespace std;
namespace Engine {
	class Scene;
	class GameEngine {
	public:
		Scene * CreateScene();
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
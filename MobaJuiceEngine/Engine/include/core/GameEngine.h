#pragma once
#include <memory>
#include "ManagerCollection.h"
#include "Scene.h"
using namespace std;
namespace Engine {
	class GameEngine {
	public:
		GameEngine();
		Scene * CreateScene(string name);
		Scene * GetActiveScene();
		void Save();
		void Save(const char *scene);
		void Load(const char *scene);

		//General Settings
		void SaveSettings(const char *settings);
		void LoadSettings(const char *settings);
		void Initialize();

		void Run();

		static ManagerCollection manager;
	private:
		std::unique_ptr<Scene> activeScene;
		const int FPS = 60;
		const int frameDelay = 1000 / FPS;
		int frameTime = 0;
		Uint32 frameStart;
	};
}
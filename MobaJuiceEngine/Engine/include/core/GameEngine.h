#pragma once
#include <memory>
#include "ManagerCollection.h"
#include "Scene.h"
using namespace std;
namespace Engine {
	class GameEngine {
	public:
		GameEngine();
		GameEngine(bool debug);
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

		struct Paths {
			enum PATH_TYPE {
				SHADER,
				ASSET,
				SETTINGS,
				ENGINE
			};
			string shaderPath;
			string assetPath;
			string settingPath;
			string enginePath;
		};

		void SetDefaultPath(Paths::PATH_TYPE type, string path);
		string GetPath(Paths::PATH_TYPE type) const;

		static ManagerCollection manager;
		static Paths path;
		static vec2 screenSize;
		static bool DEBUG;
	private:
		std::unique_ptr<Scene> activeScene;
		const int FPS = 60;
		const int frameDelay = 1000 / FPS;
		int frameTime = 0;
		Uint32 frameStart;

		//Default Engine Paths
		
	};
}
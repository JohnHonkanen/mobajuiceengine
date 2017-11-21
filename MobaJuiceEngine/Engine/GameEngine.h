#pragma once
#include <memory>

namespace Engine {
	class Scene;
	class GameEngine {
	public:
		Scene * CreateScene();
		void Save();
		void Save(const char *scene);
		void Load(const char *scene);

		void Run();
	private:
		std::unique_ptr<Scene> activeScene;

	};
}
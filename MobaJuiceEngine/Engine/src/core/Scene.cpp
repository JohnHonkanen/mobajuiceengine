#include "core/Scene.h"

namespace Engine {

	Scene::Scene() : Scene("Default")
	{
	}

	Scene::Scene(string n)
	{
		name = n;
		gameObjects = make_unique<GameObjectManager>();
	}

	Scene::~Scene()
	{
	}

	GameObjectManager * Scene::GetGameObjectManager()
	{
		return gameObjects.get();
	}
	void Scene::OnLoad()
	{
		gameObjects->OnLoad();
		skybox.GenerateSkyBox();
	}
	void Scene::Start()
	{
		gameObjects->Start();
	}
	void Scene::Input()
	{
		gameObjects->Input();
	}
	void Scene::Update()
	{
		gameObjects->Update();
	}
	void Scene::Draw()
	{
		skybox.Draw();
		gameObjects->Draw();
	}
	void Scene::AddSkyBox(string skyBoxDirectory)
	{
		skybox.SetSkyboxCubeMap(skyBoxDirectory);
	}
}


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
		hasSkyBox = skybox.GenerateSkyBox();
	}
	void Scene::Start()
	{
		gameObjects->Start();

		if (hud) {
			hud->Start();
		}
	}
	void Scene::Input()
	{
		gameObjects->Input();
	}
	void Scene::Update(double dt)
	{
		gameObjects->Update(dt);
		if (hud) 
		{
			hud->Update();
			hud->Update(dt);
		}
	}
	void Scene::Draw()
	{
		if(hasSkyBox)
			skybox.Draw();

		gameObjects->Draw();
		if (hud) {
			hud->Draw();
		}
	}
	void Scene::AddSkyBox(string skyBoxDirectory)
	{
		skybox.SetSkyboxCubeMap(skyBoxDirectory);
	}

	void Scene::AttachHUD(HUD::HUD * hud)
	{
		Scene::hud = unique_ptr<HUD::HUD>(hud);
	}
}


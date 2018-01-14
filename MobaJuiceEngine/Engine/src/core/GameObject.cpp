#include "core/GameObject.h"
#include "components/Component.h"
#include "core\GameEngine.h"

namespace Engine {
	GameObject::GameObject()
	{
		GameObject::id = -1;
		transform = make_unique<Transform>();
	}

	GameObject::GameObject(std::string name): name(name)
	{
		transform = make_unique<Transform>();
	}


	GameObject::~GameObject()
	{
	}

	void GameObject::OnLoad()
	{
		transform->OnLoad();
		for (int i = 0; i < components.size(); i++) {
			components.at(i)->transform = transform.get();
			components.at(i)->SetGameObject(this);
			components.at(i)->OnLoad();		
		}
	}

	void GameObject::Start()
	{
		for (int i = 0; i < components.size(); i++) {
			components.at(i)->Start();
		}
	}

	void GameObject::Input()
	{
		for (int i = 0; i < components.size(); i++) {
			components.at(i)->Input();
		}
	}

	void GameObject::Update()
	{
		for (int i = 0; i < components.size(); i++) {
			components.at(i)->Update();
		}
	}

	void GameObject::Draw()
	{
		for (int i = 0; i < components.size(); i++) {
			components.at(i)->Draw();
		}
	}

	GameObject * GameObject::Instantiate()
	{
		return Instantiate(transform->GetPosition(), transform->GetRotation());
	}

	GameObject * GameObject::Instantiate(vec3 position, vec3 rotation)
	{
		GameObject * copy = GameEngine::manager.gameObjectManager->CreateGameObject(name);
		copy->transform->SetPosition(position);
		copy->transform->SetEulerAngle(rotation);

		/* Copy Components to the new copy object*/
		for (int i = 0; i < components.size(); i++) {
			components.at(i)->Copy(copy);
		}

		copy->OnLoad();
		copy->Start();

		return copy;
	}

	//Adds a Component to the GameObject.
	void GameObject::AddComponent(Component *component)
	{
		component->SetGameObject(this);
		GameObject::components.push_back(ComponentUP(component));
	}
}
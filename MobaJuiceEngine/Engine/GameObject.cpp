#include "GameObject.h"
#include "Component.h"

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

	//Adds a Component to the GameObject.
	void GameObject::AddComponent(Component *component)
	{
		component->SetGameObject(this);
		GameObject::components.push_back(ComponentUP(component));
	}
}
#include "GameObject.h"
#include "Component.h"


GameObject::GameObject()
{
	GameObject::id = -1;
}


GameObject::~GameObject()
{
}

//Adds a Component to the GameObject.
void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());
	GameObject::components.push_back(component);
}
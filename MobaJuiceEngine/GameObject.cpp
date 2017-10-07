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
void GameObject::addComponent(std::unique_ptr<Component> component)
{
	component->gameObject = std::make_shared<GameObject>(this);
	GameObject:components.push_back(component);
}
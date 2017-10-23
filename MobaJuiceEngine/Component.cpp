#include "Component.h"
#include "GameObject.h"


Component::Component()
{
}


Component::~Component()
{
}
//Sets the GameoObject
void Component::SetGameObject(std::shared_ptr<GameObject> gameObject)
{
	Component::gameObject = gameObject;
	Component::transform = std::make_shared<Transform>(&gameObject->transform);
}

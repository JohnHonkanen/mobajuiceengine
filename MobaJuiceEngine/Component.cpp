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
}

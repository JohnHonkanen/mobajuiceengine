#include "Component.h"
#include "GameObject.h"


Component::Component()
{
}


Component::~Component()
{
}
//Sets the GameoObject
void Component::SetGameObject(GameObject * gameObject)
{
	Component::gameObject = gameObject;
	Component::transform = gameObject->transform.get();
}
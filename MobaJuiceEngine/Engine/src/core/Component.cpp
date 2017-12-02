#include "components\Component.h"
#include "core\GameObject.h"

namespace Engine {
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
}

#include "components\Light.h"
#include "core\GameObject.h"
namespace Engine
{
	Light * Light::Create(GameObject * gameObject, LightType type)
	{
		Light *l = new Light();
		l->properties.type = type;
		LightManager::Get()->AddLight(type, l); // Register to the light manager
		gameObject->AddComponent(l);
		return l;
	}

	Light::~Light()
	{
	}

	void Light::Copy(GameObject * object)
	{
		Light *l = Create(object, properties.type);
		l->properties = properties;
	}

	LightProperties Light::GetProperties() const
	{
		return properties;
	}

	void Light::SetLightProperties(LightProperties lightProperty)
	{
		properties = lightProperty;
	}

	void Light::SetSlot(unsigned int slot)
	{
		this->slot = slot;
	}
	void Light::RemoveFromLightManager()
	{
		LightManager::Get()->RemoveLight(properties.type, this);
	}
}


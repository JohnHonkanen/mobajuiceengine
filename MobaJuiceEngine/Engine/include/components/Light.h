#pragma once
#include "Behaviour.h"
#include "../render/LightManager.h"

namespace Engine
{
	struct LightProperties
	{
		LightType type;

		vec3 ambient = vec3(1.0f);
		vec3 diffuse = vec3(1.0f);
		vec3 specular = vec3(0.15f);

		float constant = 1.0f;
		float linear = 0.07f;
		float quadratic = 0.017f;
	};

	class Light : public Behaviour
	{
	public:
		static Light * Create(class GameObject *gameObject, LightType type);
		~Light();
		void Copy(class GameObject *object);
		LightProperties GetProperties() const;
		void SetLightProperties(LightProperties lightProperty);
		void SetSlot(unsigned int slot);
	private:
		LightProperties properties;
		unsigned int slot;
	};
}

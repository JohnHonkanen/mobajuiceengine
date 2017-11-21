/*
	Components are behaviours for the GameObject classes.
	Dev: John Honkanen
*/
#pragma once
#include <memory>
#include <string>
#include <cereal\cereal.hpp>
#include "Transform.h"
//Predefinition of a the GameObject Class

namespace Engine {
	class GameObject;
	class Component
	{
	public:
		Component();
		Component(std::string name) : name(name) {};
		~Component();
		//Only Called Once per Startup Instance of Class
		virtual void Start() {};
		//Logic Loop
		virtual void Update() {};
		//Rendering Loop
		virtual void Draw() {};

		//Serialization method
		template<class Archive>
		void serialize(Archive & ar) {
		};

		virtual void SetGameObject(GameObject * gameObject);
		GameObject *gameObject;
		Transform *transform;
		std::string name;
	};
}

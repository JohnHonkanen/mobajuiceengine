/*
	Components are behaviours for the GameObject classes.
	Dev: John Honkanen
*/
#pragma once
#include <memory>
#include <string>
#include <cereal\cereal.hpp>
#include "../core/Transform.h"
//Predefinition of a the GameObject Class

namespace Engine {
	class GameObject;
	class Component
	{
	public:
		Component();
		Component(std::string name) : name(name) {};
		virtual ~Component();
		//Called when the program is loaded
		virtual void OnLoad() {};
		//Only Called Once per Startup Instance of Class
		virtual void Start() {};
		// Input Call
		virtual void Input() {};
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

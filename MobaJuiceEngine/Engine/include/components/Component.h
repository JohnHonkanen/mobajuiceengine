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
		Component(string name) : name(name) {};
		virtual ~Component();
		//Called when the program is loaded
		virtual void OnLoad() {};
		//Only Called Once per Startup Instance of Class
		virtual void Start() {};
		// Input Call
		virtual void Input() {};
		//Logic Loop
		virtual void Update() {};
		//Logic Loop with DT
		virtual void Update(double dt) {};
		//Rendering Loop
		virtual void Draw() {};

		/* Copies the Component */
		virtual void Copy(GameObject *copyObject) = 0;

		//Serialization method
		template<class Archive>
		void serialize(Archive & ar) {
		};

		virtual void SetGameObject(GameObject * gameObject);
		GameObject *gameObject;
		Transform *transform;
		std::string name;
	protected:
		bool debugOnce = false;
	};
}

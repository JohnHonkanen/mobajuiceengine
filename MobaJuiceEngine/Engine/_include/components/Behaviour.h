/*
	Base Class for all behaviour scripts. More functionality will be filled in the future
	Dev: John Honkanen (B00291253)
*/
#pragma once
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include "Component.h"
namespace Engine {
	class Behaviour :
		public Component
	{
	public:
		Behaviour();
		Behaviour(std::string name) : Component(name) {};
		~Behaviour();
		virtual void OnLoad() {};
		//Only Called Once per Startup Instance of Class
		virtual void Start() {};
		virtual void Input() {};
		//Logic Loop
		virtual void Update() {};
		//Rendering Loop
		virtual void Draw() {};

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(isEnabled);
		}

		bool isEnabled;
	};
}
using namespace Engine;

#include <cereal/archives/xml.hpp>

CEREAL_REGISTER_TYPE(Behaviour);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Behaviour);


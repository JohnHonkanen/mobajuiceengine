#pragma once
#include "Behaviour.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
namespace Engine {
	class TextureSetter : public Behaviour {
	public:
		static TextureSetter *Create(GameObject *obj, string diffuseMap);
		void Copy(GameObject *copyObject);
		void Start();

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(diffuseMap));
		}
	private:
		string diffuseMap;
	};
}

using namespace Engine;

#include <cereal/archives/xml.hpp>
//Register camera as a derived class
CEREAL_REGISTER_TYPE(TextureSetter);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, TextureSetter);
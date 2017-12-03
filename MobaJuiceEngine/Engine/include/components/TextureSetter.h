#pragma once
#include "Behaviour.h"
namespace Engine {
	class TextureSetter : public Behaviour {
	public:
		static TextureSetter *Create(GameObject *obj, string diffuseMap);
		void Start();
	private:
		string diffuseMap;
	};
}
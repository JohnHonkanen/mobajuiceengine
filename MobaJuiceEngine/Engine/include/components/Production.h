#pragma once

#include "components\Behaviour.h"
#include "core/GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include "components\Structure.h"

using namespace std;
using namespace glm;

namespace Engine{
	class Production : public Structure {
	private:

	public:

		int storage;

		void setProduction(string type, int eff, bool act);
		void domeProduction(int eff, bool act);
		void factoryProduction(int eff, bool act);
		void update(int eff, bool act);

		int getStorage();
		void setStorage(int change);

	};
}
#include "components\Production.h"

using namespace std;

namespace Engine {

	void Production::setProduction(string type, int eff, bool act)
	{
		if (type == "dome") {
			domeProduction(eff, act);
		}
		else if (type == "factory"){
			factoryProduction(eff, act);
		}
	}

	void Production::domeProduction(int eff, bool act)
	{
		//Limits production types of building
		//based on its type
		//To be loaded in from xml
	}

	void Production::factoryProduction(int eff, bool act)
	{
		//Limits production types of building
		//based on its type
		//To be loaded in from xml
	}

	void Production::update(int eff, bool act)
	{
		if (act && storage < 100) {
			setStorage(getStorage() + 1 * eff);
		}
	}

	int Production::getStorage()
	{
		return storage;
	}

	void Production::setStorage(int change)
	{
		storage = change;
	}
}
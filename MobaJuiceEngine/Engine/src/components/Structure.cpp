#include "components\Structure.h"

using namespace std;

namespace Engine {

	Structure::Structure() {

	}

	Structure::~Structure()
	{
	}

	Structure::Structure(string building, int hp, int pow, int eff, int radOut, vec3 position, bool placed, bool active)
	{
		building = type;
		hp = health;
		pow = powerUsage;
		eff = productionEfficiency;
		radOut = radiationOutput;
		position = pos;
		placed = isPlaced;
		active = isActive;
	}

	Structure * Structure::Create(GameObject * gameObject, string building, int hp, int pow, int eff, int rad, vec3 position, bool placed, bool active)
	{
		Structure *s = new Structure(building, hp, pow, eff, rad, position, placed, active);
		gameObject->AddComponent(s);
		return s;
	}

	void Structure::OnLoad()
	{
		
	}

	string Structure::GetType()
	{
		return type;
	}

	int Structure::GetHealth()
	{
		return health;
	}

	int Structure::GetPowerusage() {
		return powerUsage;
	}

	int Structure::GetProductionEfficiency()
	{
		return productionEfficiency;
	}

	int Structure::GetRadiationOutput()
	{
		return radiationOutput;
	}

	vec3 Structure::GetPos()
	{
		return pos;
	}

	bool Structure::GetPlaced()
	{
		return isPlaced;
	}

	bool Structure::GetActive()
	{
		return isActive;
	}

	void Structure::SetHealth(int change)
	{
		health -= change;
	}

	void Structure::setPowerUsage(int change)
	{
		powerUsage += change;
	}

	void Structure::SetProductionEfficiency(int change)
	{
		productionEfficiency *= change;
	}

	void Structure::SetRadiationOutput(int change)
	{
		radiationOutput *= change;
	}

	void Structure::SetPos(vec3 change)
	{
		pos = change;
	}

	void Structure::SetPlaced(bool change)
	{
		isPlaced = change;
	}

	void Structure::SetActive(bool change)
	{
		isActive = change;
	}

}
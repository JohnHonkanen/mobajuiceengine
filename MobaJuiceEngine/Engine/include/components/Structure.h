#pragma once

#include "components\Behaviour.h"
#include "core/GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
using namespace std;
using namespace glm;

namespace Engine {
	class Structure : public Behaviour{
	private:

		string type;
		int health;						//Buildings remaining health
		int powerUsage;					//Set to 0 until power is added to game
		int productionEfficiency;		//
		int radiationOutput;			//

		vec3 pos;						//Buildings position on grid
		bool isPlaced;					//
		bool isActive;					//Turn on or off building

	public:

		Structure();
		~Structure();
		Structure(string building, int hp, int pow, int eff, int rad, vec3 position, bool placed, bool active);

		static Structure* Create(GameObject * gameObject, string building, int hp, int pow, int eff, int rad, vec3 position, bool placed, bool active);
		void Copy(GameObject *copyObject) {};

		string GetType();					//Returns buildings type
		int  GetHealth();				//Returns building health
		int  GetPowerusage();			//Returns power usage
		int  GetProductionEfficiency();	//
		int  GetRadiationOutput();		//
		vec3 GetPos();					//
		bool GetPlaced();				//
		bool GetActive();				//

		void SetHealth(int change);				//Changes buildings health
		void setPowerUsage(int change);			//Changes building power usage
		void SetProductionEfficiency(int change);	//Changes buildings
		void	 SetRadiationOutput(int change);		//
		void SetPos(vec3 change);					//
		void SetPlaced(bool change);				//
		void SetActive(bool change);				//

		void OnLoad();
		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(health), CEREAL_NVP(health), CEREAL_NVP(powerUsage), CEREAL_NVP(productionEfficiency), CEREAL_NVP(radiationOutput), CEREAL_NVP(pos), CEREAL_NVP(isPlaced), CEREAL_NVP(isActive));
		}
	};
}
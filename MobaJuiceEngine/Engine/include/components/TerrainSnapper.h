#pragma once
#include "Behaviour.h"
#include "TerrainGrid.h"
#include "core\GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>

namespace Engine {
	namespace Terrain {
		class TerrainSnapper : public Behaviour {
		public:

			static TerrainSnapper * Create(GameObject * gameObject, TerrainGrid * grid);
			void Copy(GameObject *copyObject);

			void OnLoad();
			void Start();
			void Update();		
			void SetHeldObject(GameObject *gameObject);
			
			template<class Archive>
			void serialize(Archive & ar)
			{
			}
			TerrainGrid * grid;
		private:

			vec3 CalcRayTerrainCollisionPoint();
			vec3 BinarySearchFindPoint(vec3 position, vec3 ray, float rayDist, int recursionCount);

			GameObject *heldObject;
			//TerrainGrid * grid;
			vec3 ray;
			const int RAYDIST = 600;
			const int RECURSION = 200;
		};
	}
}

using namespace Engine::Terrain;

#include <cereal/archives/xml.hpp>

CEREAL_REGISTER_TYPE(TerrainSnapper);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, TerrainSnapper);
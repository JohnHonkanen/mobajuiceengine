#pragma once
#include <vector>
#include "components\Behaviour.h"
#include "core\GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
namespace Engine {
	namespace Terrain {
		class TerrainGrid : public Behaviour
		{
		public:
			TerrainGrid();
			~TerrainGrid();

			static TerrainGrid *Create(GameObject * obj, float gridSize, unsigned xLength, unsigned zLength, float freq, 
				float weight, string shader, bool visualizeGrid);
			static TerrainGrid *Create(GameObject * obj, float gridSize, unsigned xLength, unsigned zLength, float freq, 
				float weight, string shader, bool visualizeGrid, vec3 offset);
			void OnLoad();
			void Draw();

			void GetData(vector<vec3> &verts, vector<vec2> &uv, unsigned int &xLength, unsigned int &zLength);

			template<class Archive>
			void serialize(Archive & ar)
			{
				ar(CEREAL_NVP(seed), CEREAL_NVP(gridSize), CEREAL_NVP(xLength), CEREAL_NVP(zLength), CEREAL_NVP(freq),
					CEREAL_NVP(weight), CEREAL_NVP(shader), CEREAL_NVP(visualizeGrid), CEREAL_NVP(offset.x), CEREAL_NVP(offset.y)
				, CEREAL_NVP(offset.z));
			}
		private:
			void GenerateVAO();
			void PreGenerateHeightMap();
			void BuildVertices();
			void GenerateIndices();

			string shader;

			bool preloaded = false;
			int seed = -1;
			float gridSize;
			float freq = 0.0003f;
			float weight = 30.0f;

			vector<vec3> verts;
			vector<vec2> uv;
			vector<unsigned int> indices;

			unsigned zLength;
			unsigned xLength;
			vector<vector<float>> heightmap;

			bool visualizeGrid;

			vec3 offset = vec3(0, 1, 0);
			unsigned int vao;
			unsigned int vbo[2];

		};
	}
}

using namespace Engine::Terrain;

#include <cereal/archives/xml.hpp>

CEREAL_REGISTER_TYPE(TerrainGrid);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, TerrainGrid);
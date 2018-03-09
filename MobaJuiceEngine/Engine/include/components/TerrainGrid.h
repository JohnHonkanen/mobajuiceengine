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

			void Copy(GameObject *copyObject);
			void OnLoad();
			void Draw();

			void GetData(vector<vec3> &verts, vector<vec2> &uv, vector<vec3> &normals, unsigned int &xLength, unsigned int &zLength);
			float GetHeight(float x, float z);
			vec3 GetSnapPoint(vec3 position);
			vec2 GetCoordinates(vec3 position);
			vec3 GetNormal(vec3 position);

			template<class Archive>
			void serialize(Archive & ar)
			{
				ar(CEREAL_NVP(seed), CEREAL_NVP(cellSize), CEREAL_NVP(xLength), CEREAL_NVP(zLength), CEREAL_NVP(freq),
					CEREAL_NVP(weight), CEREAL_NVP(shader), CEREAL_NVP(visualizeGrid), CEREAL_NVP(offset.x), CEREAL_NVP(offset.y)
				, CEREAL_NVP(offset.z));
			}

			vec3 offset = vec3(0, 1, 0);
		private:
			void GenerateVAO();
			void PreGenerateHeightMap();
			void BuildVertices();
			void GenerateNormals();
			void GenerateIndices();

			string shader;

			bool preloaded = false;
			int seed = -1;
			float cellSize;
			float freq = 0.0003f;
			float weight = 30.0f;

			vector<vec3> verts;
			vector<vec2> uv;
			vector<unsigned int> indices;
			vector<vec3> normals;

			unsigned zLength;
			unsigned xLength;
			vector<vector<float>> heightmap;

			bool visualizeGrid;

			unsigned int vao;
			unsigned int vbo[2];

		};

		// Derived from Youtuber(ThinMatrix) : https://www.dropbox.com/s/0md240yyc359ik3/code.txt?dl=0
		static float barryCentric(vec3 p1, vec3 p2, vec3 p3, vec2 pos) {
			float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
			float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
			float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
			float l3 = 1.0f - l1 - l2;
			return l1 * p1.y + l2 * p2.y + l3 * p3.y;
		}
	}
}

using namespace Engine::Terrain;

#include <cereal/archives/xml.hpp>

CEREAL_REGISTER_TYPE(TerrainGrid);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, TerrainGrid);
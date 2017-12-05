#pragma once
#include <vector>
#include "components\Behaviour.h"
#include "core\GameObject.h"

namespace Engine {
	namespace Terrain {
		class TerrainGrid : public Behaviour
		{
		public:
			TerrainGrid();
			~TerrainGrid();

			static TerrainGrid *Create(GameObject * obj, float gridSize, unsigned xLength, unsigned zLength, float freq, float weight, string shader, bool visualizeGrid);
			static TerrainGrid *Create(GameObject * obj, float gridSize, unsigned xLength, unsigned zLength, float freq, float weight, string shader, bool visualizeGrid, vec3 offset);
			void OnLoad();
			void Draw();

			void GetData(vector<vec3> &verts, vector<vec2> &uv, unsigned int &xLength, unsigned int &zLength);
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
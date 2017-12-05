#pragma once
#include "components\TerrainGrid.h"
#include "components\Behaviour.h"
#include "core\GameObject.h"
#include "render\Material.h"
namespace Engine {
	namespace Terrain {
		class TerrainRenderer: public Behaviour {
		public:
			static TerrainRenderer * Create(GameObject *gameObject, string diffuse, string shader);

			void OnLoad();
			void Draw();

			Material material;
		private:
			void GenerateVAO();
			void GenerateIndices();
			void GenerateNormals();

			string shader;
			TerrainGrid * grid;
			bool preloaded = false;

			vector<vec3> verts;
			vector<vec3> normals;
			vector<vec2> uv;
			vector<unsigned int> indices;

			unsigned int zLength;
			unsigned int xLength;
			float cellSize;

			unsigned int vao;
			unsigned int vbo[4];

		};
	}
}
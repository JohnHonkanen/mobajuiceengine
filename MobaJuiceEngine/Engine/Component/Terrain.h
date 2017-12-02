#pragma once
#include "../Behaviour.h"
#include <vector>
#include <glm\glm.hpp>

using namespace std;
using namespace glm;
namespace Engine {
	class Terrain : public Behaviour
	{
	public:
		Terrain();
		~Terrain();

	private:

		void BuildVertices();
		void GenerateNormals();
		void GenerateIndices();

		float gridSize;

		vector<vec3> verts;
		vector<vec3> normals;
		vector<vec2> uv;
		vector<unsigned int> indices;

		int zLength;
		int xLength;
		vector<vector<float>> heightmap;

		unsigned int vao;
		unsigned int vbo[4];
	};
}
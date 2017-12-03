#pragma once
#include "Behaviour.h"
#include <vector>
#include <glm\glm.hpp>
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include "../render/Material.h"

using namespace std;
using namespace glm;
namespace Engine {
	class Terrain : public Behaviour
	{
	public:
		Terrain();
		~Terrain();

		static Terrain* Create(GameObject * obj, float gridSize, unsigned xLength, unsigned zLength, string shader);
		static Terrain* Create(GameObject * obj, float gridSize, unsigned xLength, unsigned zLength, float freq, float weight, string shader);
		void OnLoad();
		void Draw();

		float GetHeight(float x, float z);

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(seed), CEREAL_NVP(gridSize), CEREAL_NVP(xLength), CEREAL_NVP(zLength), CEREAL_NVP(freq), CEREAL_NVP(weight), CEREAL_NVP(shader));
		}

		Material material;
	private:

		void GenerateVAO();

		void PreGenerateHeightMap();
		void BuildVertices();
		void GenerateNormals();
		void GenerateIndices();

		string shader;

		bool preloaded = false;
		int seed = -1;
		float gridSize;
		float freq = 0.0003f;
		float weight = 30.0f;

		vector<vec3> verts;
		vector<vec3> normals;
		vector<vec2> uv;
		vector<unsigned int> indices;

		unsigned zLength;
		unsigned xLength;
		vector<vector<float>> heightmap;

		unsigned int vao;
		unsigned int vbo[4];
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


using namespace Engine;
#include <cereal/archives/xml.hpp>

CEREAL_REGISTER_TYPE(Terrain);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, Terrain);
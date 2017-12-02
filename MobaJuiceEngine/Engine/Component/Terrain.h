#pragma once
#include "../Behaviour.h"
#include <vector>
#include <glm\glm.hpp>
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include "../Render/Material.h"

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

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(gridSize), CEREAL_NVP(xLength), CEREAL_NVP(zLength), CEREAL_NVP(freq), CEREAL_NVP(weight), CEREAL_NVP(shader));
		}

		Material material;
	private:

		void GenerateVAO();

		void PreGenerateHeightMap();
		void BuildVertices();
		void GenerateNormals();
		void GenerateIndices();

		string shader;

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
}


using namespace Engine;
#include <cereal/archives/xml.hpp>

CEREAL_REGISTER_TYPE(Terrain);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, Terrain);
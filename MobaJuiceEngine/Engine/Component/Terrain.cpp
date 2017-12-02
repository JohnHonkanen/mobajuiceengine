#include "Terrain.h"
#include "../_Libs/simplex/SimplexNoise.h"
namespace Engine {
	Terrain::Terrain()
	{
	}
	Terrain::~Terrain()
	{
	}
	void Terrain::BuildVertices()
	{
		verts.resize( zLength * xLength);
		uv.resize(verts.size());

		float texU = 1.0f, texV = 1.0f;
		float freq = 0.0003f;
		float weight = 30.0f;

		for (int z = 0; z < zLength; z++) {
			for (int x = 0; x < xLength; x++) {

				float scaleU = z / float(zLength - 1);
				float scaleV = x / float(xLength - 1);

				float height;
				//Single Pass heightmap
				height = SimplexNoise::noise(x * freq *);
			}
		}
	}
	void Terrain::GenerateNormals()
	{
	}
	void Terrain::GenerateIndices()
	{
	}
}


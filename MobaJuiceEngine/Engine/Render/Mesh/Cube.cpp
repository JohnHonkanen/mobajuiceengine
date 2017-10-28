#include "Cube.h"

namespace Engine {
	Cube::Cube()
	{
	}

	void Cube::Init()
	{
		float vertices[] = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		Cube::data.vertexArray = std::vector<float>(vertices, vertices + sizeof vertices / sizeof vertices[0]);
		Cube::data.indices = std::vector<unsigned int>(indices, indices + sizeof indices / sizeof indices[0]);
		Cube::data.indexCount = 6;
		Cube::data.numVerts = 4;
	}
}
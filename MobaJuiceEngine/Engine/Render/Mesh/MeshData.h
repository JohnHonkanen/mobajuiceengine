/*
	Mesh data for meshes in primitive types.
	Dev: John Honkanen
*/
#include <vector>
#pragma once
struct MeshData {
	std::vector<float> vertexArray;
	std::vector<float> normalArray;
	std::vector<float> uvArray;
	std::vector<unsigned int> indices;
	unsigned int numVerts;
	unsigned int indexCount;
};
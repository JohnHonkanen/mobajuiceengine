/*
	Mesh data for meshes in primitive types.
	Dev: John Honkanen
*/

#pragma once
struct MeshData {
	float *vertexArray;
	float *normalArray;
	float *uvArray;
	int numVerts;
};
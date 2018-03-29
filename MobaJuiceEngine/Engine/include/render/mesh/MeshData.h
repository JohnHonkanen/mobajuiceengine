/*
	Mesh data for meshes in primitive types.
	Dev: John Honkanen
*/
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#pragma once
namespace Engine {
	struct MeshData {
		std::vector<GLfloat> vertexArray;
		std::vector<GLfloat> normalArray;
		std::vector<GLfloat> uvArray;
		std::vector<GLuint> indices;
		GLuint numVerts;
		GLuint indexCount;
		glm::vec3 boundingBox;
	};
}
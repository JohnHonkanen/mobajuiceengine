#pragma once
#include "Mesh.h"
#include "MeshData.h"
#include "../../Dictionary.h"
#include "Shape.h"
#include <memory>
#include <GL\glew.h>
#include <map>

#define STORED_VERTEX       0
#define STORED_COLOR        1
#define STORED_UV           2
#define STORED_NORMAL		3
#define STORED_INDEX		4
#define STORED_TANGENT		5
#define STORED_BITANGENT	6

class OGLMeshManager {
public:
	OGLMeshManager() {};
	~OGLMeshManager();
	std::shared_ptr<Mesh> GetMesh(std::string path);
	void CreateMesh(std::string path);
	void CreateMesh(std::string path, Shape *shape);
private:
	
	GLuint GenerateVAO(MeshData data);

	std::map<std::string, std::shared_ptr<Mesh>> meshDictionary;
	std::map<GLuint, GLuint*> VAOMap;
};
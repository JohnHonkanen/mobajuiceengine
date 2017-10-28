#include "OGLMeshManager.h"
#include "OGLMesh.h"
OGLMeshManager::~OGLMeshManager()
{
	//Properly de-allocate all resources once they've outlived their purpose
	//A VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER. This means it stores its unbind calls
	//so make sure you don't unbind the element array buffer before unbinding your VAO, otherwise it doesn't have an EBO
	//configured. 

	std::map<GLuint, GLuint*>::iterator it = VAOMap.begin();

	for (it; it == VAOMap.end(); it++) {
		glDeleteVertexArrays(1, &it->first);
		glDeleteBuffers(1, &it->second[STORED_VERTEX]);
		glDeleteBuffers(1, &it->second[STORED_COLOR]);
		glDeleteBuffers(1, &it->second[STORED_UV]);
		glDeleteBuffers(1, &it->second[STORED_NORMAL]);
		glDeleteBuffers(1, &it->second[STORED_INDEX]);
		glDeleteBuffers(1, &it->second[STORED_TANGENT]);
		glDeleteBuffers(1, &it->second[STORED_BITANGENT]);

	}

}

Mesh * OGLMeshManager::GetMesh(std::string path)
{
	auto it = meshDictionary.find(path);
	if (it != meshDictionary.end()) {
		return meshDictionary[path].get();
	}

	OGLMeshManager::CreateMesh(path);

	return meshDictionary[path].get();
}

/*
	Create out mesh using Assimp via the Model Path
	@param path path to the model file
*/
void OGLMeshManager::CreateMesh(std::string path)
{
	OGLMesh *oglMesh = new OGLMesh(path, new AiModel(path)); //Sets up the AIModel and MeshData
	oglMesh->SetVAO(GenerateVAO(oglMesh->GetMeshData()));

	meshDictionary.insert(std::pair<std::string, MeshUniqPtr >(path, MeshUniqPtr(oglMesh)));
}

void OGLMeshManager::CreateMesh(std::string path, Shape * shape)
{
	OGLMesh *oglMesh = new OGLMesh(path, shape); //Sets up the AIModle and MeshData
	oglMesh->SetVAO(GenerateVAO(oglMesh->GetMeshData()));

	meshDictionary.insert(std::pair<std::string, MeshUniqPtr >(path, MeshUniqPtr(oglMesh)));
}


GLuint OGLMeshManager::GenerateVAO(MeshData data)
{
	GLuint VAO;
	GLuint vertexBuffer, uvBuffer, normalBuffer, elementBuffer;
	GLuint* meshBuffers = new GLuint[4];

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &elementBuffer);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * data.numVerts * sizeof(GLfloat), &data.vertexArray[0], GL_STATIC_DRAW);

	meshBuffers[STORED_VERTEX] = vertexBuffer;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indexCount * sizeof(GLuint), &data.indices[0], GL_STATIC_DRAW);

	meshBuffers[STORED_INDEX] = elementBuffer;

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	if (!data.uvArray.empty()) {
		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, 2 * data.numVerts * sizeof(GLfloat), &data.uvArray[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(2);
		meshBuffers[STORED_UV] = uvBuffer;
	}

	// Normals attribute
	if (!data.normalArray.empty()) {
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, 3 * data.numVerts * sizeof(GLfloat), &data.normalArray[0], GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); //3 * sizeof(GLfloat)
		glEnableVertexAttribArray(3); // Set location in shader
		meshBuffers[STORED_NORMAL] = normalBuffer;
	}

	glBindVertexArray(0); // Unbind VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	VAOMap.insert(std::pair<GLuint, GLuint *>(VAO, meshBuffers));
	return VAO;
}

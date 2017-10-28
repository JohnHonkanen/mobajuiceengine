#include "OGLMesh.h"

OGLMesh::OGLMesh(std::string name, Shape *shape)
{
	OGLMesh::name = name;
	OGLMesh::model = std::unique_ptr<Shape>(shape);
	OGLMesh::model->Init();
}

OGLMesh::~OGLMesh()
{
}

void OGLMesh::Render()
{
	MeshData data = OGLMesh::GetMeshData();
	glBindVertexArray(OGLMesh::VAO);
	glDrawElements(GL_TRIANGLES, data.indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void OGLMesh::SetVAO(GLuint VAO)
{
	OGLMesh::VAO = VAO;
}

const MeshData OGLMesh::GetMeshData()
{
	return model->getMeshData();
}

#include "OGLMesh.h"
namespace Engine {
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
		std::vector<MeshData> data = OGLMesh::GetMeshData();
		for (int i = 0; i < data.size(); i++) {
			glBindVertexArray(OGLMesh::VAO[i]);
			glDrawElements(GL_TRIANGLES, data[i].indexCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		
	}

	void OGLMesh::SetVAO(GLuint vao)
	{
		VAO.push_back(vao);
	}

	const std::vector<MeshData> OGLMesh::GetMeshData()
	{
		return model->getMeshData();
	}
}

#include "render/mesh/OGLMesh.h"
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
		GLuint shader = shaderManager->GetShader(OGLMesh::GetShader());
		std::vector<MeshData> data = OGLMesh::GetMeshData();
		std::vector<Material> materials = OGLMesh::GetMaterials();
		for (int i = 0; i < data.size(); i++) {
			if (materials[i].diffuseMap != "") {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(materials[i].diffuseMap));
				glUniform1i(glGetUniformLocation(shader, "diffuseMap"), 0);
			}
			
			glBindVertexArray(OGLMesh::VAO[i]);
			glDrawElements(GL_TRIANGLES, data[i].indexCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		/*int test = 1;
		if (materials[test].diffuseMap != "") {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(materials[test].diffuseMap));
			glUniform1i(glGetUniformLocation(shader, "diffuseMap"), 0);
		}

		glBindVertexArray(OGLMesh::VAO[test]);
		glDrawElements(GL_TRIANGLES, data[test].indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);*/
		
	}

	void OGLMesh::SetVAO(GLuint vao)
	{
		VAO.push_back(vao);
	}

	const std::vector<MeshData> OGLMesh::GetMeshData()
	{
		return model->getMeshData();
	}
	const std::vector<Material> OGLMesh::GetMaterials()
	{
		return model->getMaterials();
	}
	Material * OGLMesh::GetMaterial()
	{
		return model->GetMaterial();
	}
	void OGLMesh::SetShaderProgram(string shader, ShaderManager *shaderManager)
	{
		model->setShaderProgram(shader);
		OGLMesh::shaderManager = shaderManager;
	}
	void OGLMesh::SetTextureManager(TextureManager * textureManager)
	{
		OGLMesh::textureManager = textureManager;
	}
	string OGLMesh::GetShader()
	{
		return  model->getMaterials()[0].shader;
	}
	std::vector<unsigned int> OGLMesh::getID()
	{
		return VAO;
	}
}

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

	void OGLMesh::Render(Material *material)
	{
		GLuint shader = shaderManager->GetShader(OGLMesh::GetShader());
		std::vector<MeshData> data = OGLMesh::GetMeshData();
		std::vector<Material> materials = OGLMesh::GetMaterials();
		for (int i = 0; i < data.size(); i++) {
			if (material->diffuseMap != "")
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(material->diffuseMap));
				glUniform1i(glGetUniformLocation(shader, "diffuseMap"), 0);

			}
			else {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (material->specularMap != "")
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(material->specularMap));
				glUniform1i(glGetUniformLocation(shader, "specularMap"), 1);
			}
			else {
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (material->emissionMap != "")
			{
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(material->specularMap));
				glUniform1i(glGetUniformLocation(shader, "emissionMap"), 2);
			}
			else {
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (material->normalMap != "")
			{
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(material->normalMap));
				glUniform1i(glGetUniformLocation(shader, "normalMap"), 3);

			}
			else {
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
			
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

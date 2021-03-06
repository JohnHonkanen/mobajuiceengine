#pragma once
#include <GL\glew.h>
#include <memory>
#include <vector>
#include "Mesh.h"
#include "AiModel.h"
#include "../ShaderManager.h"
#include "../texture/TextureManager.h"
namespace Engine {
	class OGLMesh : public Mesh {
	public:
		OGLMesh(std::string name, Shape *shape);
		~OGLMesh();
		void Render(Material *material);
		void SetVAO(GLuint VAO);
		const std::vector<MeshData> GetMeshData();
		const std::vector<Material> GetMaterials();
		Material * GetMaterial();
		void SetShaderProgram(string shader, ShaderManager *shaderManager);
		void SetTextureManager(TextureManager *textureManager);
		string GetShader();
		virtual std::vector<unsigned int> getID();
	private:
		std::string name;
		std::unique_ptr<Shape> model;
		std::vector<GLuint> VAO;
		ShaderManager *shaderManager;
		TextureManager *textureManager;
	};
}

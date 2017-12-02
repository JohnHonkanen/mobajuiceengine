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
		void Render();
		void SetVAO(GLuint VAO);
		const std::vector<MeshData> GetMeshData();
		const std::vector<Material> GetMaterials();
		void SetShaderProgram(string shader, ShaderManager *shaderManager);
		void SetTextureManager(TextureManager *textureManager);
		string GetShader();
	private:
		std::string name;
		std::unique_ptr<Shape> model;
		std::vector<GLuint> VAO;
		ShaderManager *shaderManager;
		TextureManager *textureManager;
	};
}

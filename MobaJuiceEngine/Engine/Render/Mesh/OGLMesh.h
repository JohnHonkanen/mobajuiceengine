#pragma once
#include <GL\glew.h>
#include <memory>
#include "Mesh.h"
#include "AiModel.h"
namespace Engine {
	class OGLMesh : public Mesh {
	public:
		OGLMesh(std::string name, Shape *shape);
		~OGLMesh();
		void Render();
		void SetVAO(GLuint VAO);
		const MeshData GetMeshData();
	private:
		std::string name;
		std::unique_ptr<Shape> model;
		GLuint VAO;
	};
}

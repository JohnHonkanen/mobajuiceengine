#pragma once
#include "../Behaviour.h"
#include "../Render/Mesh/Mesh.h"
#include "../Render/Mesh/OGLMeshManager.h"
#include "../Render/Renderer.h"
#include "../Render/OGLShader.h"
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

namespace Engine {

	class MeshRenderer : public Behaviour, Renderer
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		void Start();
		void Draw();

		//Temp Function
		void SetUpMesh(OGLMeshManager * manager);
		void SetShader(OGLShader *s);
		std::string meshPath;
	private:
		Mesh *mesh;
		OGLShader *shader;
	};
}
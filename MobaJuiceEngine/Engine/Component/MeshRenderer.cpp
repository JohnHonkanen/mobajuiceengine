#include "MeshRenderer.h"
#include "Camera.h"
#include "../GameObject.h"
namespace Engine {
	MeshRenderer::MeshRenderer()
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	MeshRenderer * MeshRenderer::Create(GameObject *gameObject, std::string path, OGLMeshManager * manager)
	{
		MeshRenderer *r = new MeshRenderer();
		r->meshPath = path;
		r->mesh = manager->GetMesh(path);
		r->meshManager = manager;
		//Adds ownership
		gameObject->AddComponent(r);

		return r;
	}

	void MeshRenderer::Start()
	{
	}

	void MeshRenderer::Draw()
	{
		string shaderString = mesh->GetShader();
		GLuint shader = meshManager->getShaderManager()->GetShader(shaderString);
		glUseProgram(shader);
		//SetMVPS
		glm::mat4 projection(1.0);
		projection = Camera::mainCamera->GetProjectionMatrix();
		glm::mat4 model(1.0);
		Camera::mainCamera->CalculateViewMatrix();
		glm::mat4 view = Camera::mainCamera->GetViewMatrix();

		model = transform->GetLocalToWorldMatrix();
		/*glDepthMask(GL_TRUE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);*/

		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//ENDOFMVP
		mesh->Render();
	}
}

#include "MeshRenderer.h"
#include "Camera.h"
namespace Engine {
	MeshRenderer::MeshRenderer()
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Start()
	{
	}

	void MeshRenderer::Draw()
	{
		shader->Use();
		//SetMVPS
		glm::mat4 projection(1.0);
		projection = Camera::mainCamera->GetProjectionMatrix();
		glm::mat4 model(1.0);
		glm::mat4 view = Camera::mainCamera->GetViewMatrix();

		model = transform->GetLocalToWorldMatrix();


		/*Temp Code to be move to Materials*/
		glm::vec3 objectColor(1.0f, 0.5f, 0.31f);
		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(glGetUniformLocation(shader->program, "objectColor"), 1, glm::value_ptr(objectColor));
		glUniform3fv(glGetUniformLocation(shader->program, "lightColor"), 1, glm::value_ptr(lightColor));
		glUniform3fv(glGetUniformLocation(shader->program, "lightPos"), 1, glm::value_ptr(lightPos));
		//ENDOFMVP
		mesh->Render();
	}

	void MeshRenderer::SetUpMesh(OGLMeshManager * manager)
	{
		mesh = manager->GetMesh(meshPath);
	}

	void MeshRenderer::SetShader(OGLShader * s)
	{
		shader = s;
	}
}

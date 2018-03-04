#include "components/MeshRenderer.h"
#include "components/Camera.h"
#include "core/GameObject.h"
#include "core/GameEngine.h"
namespace Engine {
	MeshRenderer::MeshRenderer()
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	MeshRenderer * MeshRenderer::Create(GameObject *gameObject, std::string path)
	{
		MeshRenderer *r = new MeshRenderer();
		r->meshPath = path;
		r->partialRenderValue = 3000; //Default Value
		r->cullBackFace = true;
		//Adds ownership
		gameObject->AddComponent(r);

		return r;
	}

	void MeshRenderer::Copy(GameObject * copyObject)
	{
		MeshRenderer *copy = new MeshRenderer();

		copy->meshPath = MeshRenderer::meshPath;

		copyObject->AddComponent(copy);
	}

	void MeshRenderer::OnLoad()
	{
		meshManager = &GameEngine::manager.meshManager;
		mesh = meshManager->GetMesh(meshPath);
		material = mesh->GetMaterial();
		
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
		glDepthMask(GL_TRUE);
		if (!cullBackFace)
		{
			glDisable(GL_CULL_FACE);
		}
		/*
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);*/

		glm::vec3 objectColor(1.0f, 0.5f, 0.31f);
		glm::vec3 lightColor(1.0f, 1.0f, 1.0f); 
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(glGetUniformLocation(shader, "objectColor"), 1, glm::value_ptr(objectColor));
		glUniform3fv(glGetUniformLocation(shader, "lightColor"), 1, glm::value_ptr(lightColor));
		glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1, glm::value_ptr(lightPos));
		glUniform1f(glGetUniformLocation(shader, "partialRenderV"), partialRenderValue);
		//ENDOFMVP

		mesh->Render(gameObject->material);

		if (!cullBackFace)
		{
			glEnable(GL_CULL_FACE);
		}
	}
}

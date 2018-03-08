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

	MeshRenderer * MeshRenderer::Create(GameObject *gameObject, std::string path, RenderMode mode = FORWARD)
	{
		MeshRenderer *r = new MeshRenderer();
		r->meshPath = path;
		r->partialRenderValue = 3000; //Default Value
		r->cullBackFace = true;
		//Adds ownership
		gameObject->AddComponent(r);

		r->gameObject->SetRenderMode(mode);

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
		GLuint shader;

		if (gameObject->GetRenderMode() == DEFERRED)
		{
			shader = meshManager->getShaderManager()->GetShader(gameObject->material->shader);
		}
		else {
			shader = meshManager->getShaderManager()->GetShader(shaderString);
		}
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

		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glUniform1f(glGetUniformLocation(shader, "partialRenderV"), partialRenderValue);
		//ENDOFMVP

		mesh->Render(gameObject->material);

		if (!cullBackFace)
		{
			glEnable(GL_CULL_FACE);
		}
	}
}

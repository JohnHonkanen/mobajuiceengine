#include "render\mesh\Skybox.h"
#include "core\GameEngine.h"
#include <GL\glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "components\Camera.h"

namespace Engine {
	Skybox::Skybox()
	{
	}
	Skybox::~Skybox()
	{
	}
	void Skybox::Draw()
	{
		if (skyboxTexture == 0)
			return;

		glDepthMask(GL_FALSE);
		glCullFace(GL_FRONT);

		glUseProgram(program);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
		glUniform1i(glGetUniformLocation(program, "texture0"), 0);

		mat4 projection, view;
		projection = Camera::mainCamera->GetProjectionMatrix();
		Camera::mainCamera->CalculateViewMatrix();
		view = mat4(mat3(Camera::mainCamera->GetViewMatrix()));

		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glDepthMask(GL_TRUE);
		glCullFace(GL_BACK);
	}

	void Skybox::SetSkyboxCubeMap(string directory)
	{
		cubeMap = directory;
	}

	void Skybox::GenerateSkyBox()
	{
		skyboxTexture = GameEngine::manager.textureManager.getTexture(cubeMap, true);
		vao = GameEngine::manager.meshManager.GetMesh(cube)->getID()[0];
		program = GameEngine::manager.shaderManager.GetShader(shader);

		model = mat4(1.0);
		model = scale(model, vec3(10.0f));
	}
}

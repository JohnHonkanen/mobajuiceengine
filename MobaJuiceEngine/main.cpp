#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#define DEG_TO_RAD 0.017453293

#include <iostream>
#include <memory>
#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Render\GraphicsHandlers\OGLGraphicHandler.h"
#include "Render\Window\SDLWindow.h"
#include "Render\Mesh\OGLMeshManager.h"
#include "Render\OGLShader.h"
#include "Render\Mesh\Cube.h"
#include "GameObject.h"
using namespace std;
using namespace glm;

int main(int argc, char *argv[]){

	OGLGraphicHandler graphicsHandler(new SDLWindow("MobaJuice", 800, 800));
	graphicsHandler.Initialize();

	OGLShader baseProgram("phong", "Assets/Shaders/textured.vert", "Assets/Shaders/textured.frag");

	std::string path = "Assets/Crate/deer.fbx";
	OGLMeshManager *meshManager = new OGLMeshManager();

	meshManager->CreateMesh("Cube", new Cube());
	Mesh *mesh = meshManager->GetMesh(path).get();

	Transform transform;
	//transform.SetScale(glm::vec3(0.003f, 0.003f, 0.003f));
	transform.SetPosition(glm::vec3(-0.0f, -3.0f, -7.0f));
	transform.SetEulerAngle(glm::vec3(0.0f, -50.0f, 0.0f));

	Transform pTransform;
	pTransform.SetPosition(glm::vec3(-2.0f, -3.0, -0.0f));
	pTransform.SetEulerAngle(glm::vec3(-90.0f, 0.0f, 0.0f));
	pTransform.SetScale(glm::vec3(0.003f, 0.003f, 0.003f));
	
	transform.AddChildren(pTransform);

	GameObject object;



	//Temp Loop
	//genTris();
	float r = 180.0f;
	SDL_Event sdlEvent;  // variable to detect SDL events
	bool running = true; // set running to true
	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT)
				running = false;
		}
		r += 0.1;
		//Loop for Graphics
		graphicsHandler.Start();
		baseProgram.Use();
		//PlaceHolder Code
		//drawVAO();
		//SetMVPS
		glm::mat4 projection(1.0);
		projection = glm::perspective(float(60.0f*DEG_TO_RAD), 800.0f / 600.0f, 1.0f, 1000.0f);
		glm::mat4 model(1.0);
		glm::mat4 view(1.0);

		glm::vec3 angle;

		Transform* parent = pTransform.GetParent();
		angle = parent->GetRotation();
		parent->SetEulerAngle(glm::vec3(r, r, angle.z));
		model = parent->GetLocalToWorldMatrix(model);

		angle = pTransform.GetRotation();
		pTransform.SetEulerAngle(glm::vec3(angle.x,r*2, angle.z));
		
		
		model = pTransform.GetLocalToWorldMatrix();

		

		glm::vec3 objectColor(1.0f,0.5f,0.31f);
		glm::vec3 lightColor(1.0f,1.0f,1.0f);
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		glUniformMatrix4fv(glGetUniformLocation(baseProgram.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(baseProgram.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(baseProgram.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(glGetUniformLocation(baseProgram.program, "objectColor"), 1, glm::value_ptr(objectColor));
		glUniform3fv(glGetUniformLocation(baseProgram.program, "lightColor"), 1, glm::value_ptr(lightColor));
		glUniform3fv(glGetUniformLocation(baseProgram.program, "lightPos"), 1, glm::value_ptr(lightPos));
		//ENDOFMVP
		mesh->Render();
		//EndOfPlaceHolder
		graphicsHandler.End();
	}
	
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	graphicsHandler.Destroy();
	delete meshManager;
	return 0;
}
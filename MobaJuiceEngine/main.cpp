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
using namespace std;
using namespace glm;

int main(int argc, char *argv[]){

	OGLGraphicHandler graphicsHandler(new SDLWindow("MobaJuice", 800, 800));
	graphicsHandler.Initialize();

	OGLShader baseProgram("phong", "Assets/Shaders/textured.vert", "Assets/Shaders/textured.frag");

	std::string path = "Assets/Crate/STONE.dae";
	OGLMeshManager *meshManager = new OGLMeshManager();

	meshManager->CreateMesh("Cube", new Cube());
	Mesh *mesh = meshManager->GetMesh("Cube").get();

	//Temp Loop
	//genTris();
	SDL_Event sdlEvent;  // variable to detect SDL events
	bool running = true; // set running to true
	while (running) {
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT)
				running = false;
		}
		//Loop for Graphics
		graphicsHandler.Start();
		baseProgram.Use();
		//PlaceHolder Code
		//drawVAO();
		//SetMVPS
		glm::mat4 projection(1.0);
		projection = glm::perspective(float(60.0f*DEG_TO_RAD), 800.0f / 600.0f, 1.0f, 50.0f);
		glm::mat4 modelview(1.0);
		modelview = glm::translate(modelview, glm::vec3(-10.0f, -0.1f, -10.0f));

		glUniformMatrix4fv(glGetUniformLocation(baseProgram.program, "projection;"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(baseProgram.program, "modelview;"), 1, GL_FALSE, glm::value_ptr(modelview));
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
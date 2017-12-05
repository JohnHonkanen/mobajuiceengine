#pragma once
#include <glm\glm.hpp>
#include <string>

using namespace glm;
using namespace std;

namespace Engine {
	class Skybox {
	public:
		Skybox();
		~Skybox();
		bool GenerateSkyBox();

		void Draw();

		void SetSkyboxCubeMap(string directory);
	private:

		

		string cube = "Assets/Models/cube/cube.obj";
		string shader = "skyBoxShader";
		unsigned int program;
		unsigned int vao;
		unsigned int skyboxTexture;
		string cubeMap;
		mat4 model;
		
	};
}
#include "render/ShaderManager.h"

namespace Engine {
	ShaderManager::ShaderManager()
	{
	}
	ShaderManager::~ShaderManager()
	{
	}
	OGLShader * ShaderManager::CreateShader(std::string name, const char * vertexPath, const char * fragmentPath)
	{
		shaders.insert(pair<string, ShaderUptr>(name, make_unique<OGLShader>(name, vertexPath, fragmentPath)));

		return shaders[name].get();
	}
	GLuint ShaderManager::GetShader(std::string name)
	{
		auto it = shaders.find(name);
		if (it != shaders.end()) {
			return shaders[name]->program;
		}

		return 0;
	}
	OGLShader * ShaderManager::GetShaderProgram(std::string name)
	{
		auto it = shaders.find(name);
		if (it != shaders.end()) {
			return shaders[name].get();
		}

		return nullptr;
	}
}


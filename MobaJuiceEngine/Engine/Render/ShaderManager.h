#pragma once
#include <map>
#include <memory>
#include "OGLShader.h"

using namespace std;

namespace Engine {
	typedef std::unique_ptr<OGLShader> ShaderUptr;

	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();

		OGLShader * CreateShader(std::string name, const char *vertexPath, const char *fragmentPath);
		GLuint GetShader(std::string name);
	private:
		map<string, ShaderUptr> shaders;
	};
}
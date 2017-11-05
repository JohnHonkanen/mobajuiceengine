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

		OGLShader * CreateShader();
	private:
		map<string, ShaderUptr> shaders;
	};
}
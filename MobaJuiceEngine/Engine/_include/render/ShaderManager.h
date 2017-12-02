/*
	The ShaderManager class used to control and manage shaders.
	Dev: John Honkanen (B00291253)
*/
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

		/*
			Creates the shader, and assigns ownership to this Shader Manager
			@param name			name slug of the shader
			@param vertexPath	Path to the vertex shader file
			@param fragmentPath	Path to the fragment shader file
			@return	Return the newly made shader
		*/
		OGLShader * CreateShader(std::string name, const char *vertexPath, const char *fragmentPath);
		/*
			Gets the shader with this slug
		*/
		GLuint GetShader(std::string name);
	private:
		map<string, ShaderUptr> shaders;
	};
}
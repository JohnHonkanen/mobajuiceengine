/*
	OpenGL implementation facade for Shaders
	Dev: John Honkanen
*/

#pragma once
#include<GL\glew.h>
#include "Shader.h"
class OGLShader : public Shader
{
public:
	OGLShader(std::string name, const char *vertexPath, const char *fragmentPath);
	~OGLShader();
	void Use();
protected:
	void Load(const char *vertexPath, const char *fragmentPath);
	GLuint program;
};


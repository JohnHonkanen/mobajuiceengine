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
	//Intialize the class, with a shader name and specify the path the vertex and fragment shaders.
	OGLShader(std::string name, const char *vertexPath, const char *fragmentPath);
	~OGLShader();
	//Use the shader
	void Use();
	GLuint program;
protected:
	//Load the vertex and fragment shader into memory
	void Load(const char *vertexPath, const char *fragmentPath);
private:
	
};


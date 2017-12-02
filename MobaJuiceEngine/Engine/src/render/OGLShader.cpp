#include "render/OGLShader.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
namespace Engine {
	/*
		Intialize the class, with a shader name and specify the path the vertex and fragment shaders.
		@param name			name of the shader
		@param vertexPath	path to the vertex shader
		@param fragmentPath	path to the fragment shader
	*/
	OGLShader::OGLShader(std::string name, const char * vertexPath, const char * fragmentPath) : Shader(name)
	{
		OGLShader::Load(vertexPath, fragmentPath);
	}

	OGLShader::~OGLShader()
	{
	}
	//Use the Shader program using glUseProgram()
	void OGLShader::Use()
	{
		glUseProgram(this->program);
	}

	/*
		Reads and Load our Shaders into a shader program.
		@param vertexPath	path to the vertex shader
		@param fragmentPath	path to the fragment shader
	*/
	void OGLShader::Load(const char * vertexPath, const char * fragmentPath)
	{
		// 1. Retrieve the vertex/fragment source code from destination file path.
		string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;

		// Ensure ifsteam objects can throw exceptions.
		vShaderFile.exceptions(ifstream::badbit);
		fShaderFile.exceptions(ifstream::badbit);

		try {
			// Open Shader files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			stringstream vShaderStream, fShaderStream;

			// Read Shader file's buffer content into streams.
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			// Close Shader Files
			vShaderFile.close();
			fShaderFile.close();

			// Convert Shader file streams into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (ifstream::failure e) {
			cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		}
		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar *fShaderCode = fragmentCode.c_str();

		// 2. Compile Shader and get length of each
		GLint vlen;
		GLint flen;
		GLuint vertex, fragment;
		GLint success;

		GLchar infoLog[512];

		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		// Print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}

		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		// Print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
		}

		// Shader Program
		this->program = glCreateProgram();
		glAttachShader(this->program, vertex);
		glAttachShader(this->program, fragment);
		glLinkProgram(this->program);

		// Print linking errors if any
		glGetProgramiv(this->program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->program, 512, NULL, infoLog);
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
}
/*
	Shader Interface
	Dev: John Honkanen
*/
#pragma once
#include<utility>
#include<string>

class Shader
{
public:
	Shader(std::string name);
	~Shader();
	//Use the Shader Program
	virtual void Use() = 0;
	const std::string getName();
protected:
	//Read and Load the Shader Program
	virtual void Load(const char *vertexPath, const char *fragmentPath) = 0;
	std::string name;

};


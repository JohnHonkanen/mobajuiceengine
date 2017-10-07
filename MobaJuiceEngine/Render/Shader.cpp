#include "Shader.h"

using namespace std;

Shader::Shader(std::string n)
{
	name = n;
}

Shader::~Shader()
{
}

//Returns a read-only value for the name
const std::string Shader::getName()
{
	return name;
}

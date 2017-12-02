#include "render/Shader.h"

using namespace std;
namespace Engine {
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
}

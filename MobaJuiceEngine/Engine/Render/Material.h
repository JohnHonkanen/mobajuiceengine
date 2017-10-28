/*
	Material holding the string map values to the Texture and Shader dictionary
	Dev: John Honkanen
*/
#pragma once
#include <string>
#include <glm\glm.hpp>
class Material
{
public:
	std::string shader;
	std::string albedoMap; //Color Map
	std::string normalMap;
	std::string occulusionMap;
	std::string emissionMap;
	std::string alphaMap;

	glm::vec4 color;
	glm::vec4 specular;
	glm::vec4 diffuse;
	float shininess;
};

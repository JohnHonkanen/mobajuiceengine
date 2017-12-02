/*
	Material holding the string map values to the Texture and Shader dictionary
	Dev: John Honkanen
*/
#pragma once
#include <string>
#include <glm\glm.hpp>
namespace Engine {
	class Material
	{
	public:
		std::string shader;
		std::string diffuseMap; //Color Map
		std::string normalMap;
		std::string specularMap;
		std::string occulusionMap;
		std::string emissionMap;
		std::string alphaMap;

		glm::vec4 color;
		glm::vec4 specular;
		glm::vec4 diffuse;
		float shininess;
	};
}
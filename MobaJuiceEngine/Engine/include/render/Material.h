/*
	Material holding the string map values to the Texture and Shader dictionary
	Dev: John Honkanen
*/
#pragma once
#include <string>
#include <glm\glm.hpp>
#include <cereal\cereal.hpp>
#include <cereal/archives/xml.hpp>

namespace Engine {
	class Material
	{
	public:

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(shader), CEREAL_NVP(diffuseMap), CEREAL_NVP(normalMap), CEREAL_NVP(specularMap), CEREAL_NVP(occulusionMap), 
				CEREAL_NVP(emissionMap), CEREAL_NVP(alphaMap), CEREAL_NVP(color.x), CEREAL_NVP(color.y), CEREAL_NVP(color.z), 
				CEREAL_NVP(specular.x), CEREAL_NVP(specular.y), CEREAL_NVP(specular.z), CEREAL_NVP(diffuse.x), CEREAL_NVP(diffuse.y),
				CEREAL_NVP(diffuse.z), CEREAL_NVP(shininess));
		}

		Material *Copy();
		std::string shader;
		std::string diffuseMap; //Color Map
		std::string altDiffuseMap; //Secondary DiffuseMap
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

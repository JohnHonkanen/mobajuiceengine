#pragma once

#include <glm\glm.hpp>

namespace Engine{
	namespace RaycastUtility {
		/*Tranform coords into 3D normalised device coordinates. In the range of x [-1:1] y [-1:1] and z [-1:1]*/
		glm::vec3 ConvertPointToNormalizeCoords(const int x, const int y, const int width,const int height);
		/*Transform coords into Homogeneous Clip Coordinates*/
		glm::vec4 ConvertPointToHomoCoords(glm::vec3 normalizedCoords); 
		/*Transform coords into eye/view coordinates*/
		glm::vec4 ConvertPointToViewCoords(glm::vec4 homogeneousCoords, glm::mat4 projectionMatrix);
		/*Transform view coords into world coords*/
		glm::vec4 ConvertPointToWorldCoords(glm::vec4 viewCoords, glm::mat4 viewMatrix);
		/*Transforms Normalized Coords into world coords*/
		glm::vec4 ConvertNormalizedCoordsToWorldCoords(glm::vec3 normalizedCoords, glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

	}
}
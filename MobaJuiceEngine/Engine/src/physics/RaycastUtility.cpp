#include "physics/RaycastUtility.h"

namespace Engine{
	namespace RaycastUtility {
		glm::vec3 ConvertPointToNormalizeCoords(const int x, const int y, const int width, const int height)
		{
			float X = (2.0f * x) / width - 1.0f;
			float Y = 1.0f - (2.0f * y) / height;
			float Z = 1.0f;


			return glm::vec3(X, Y, Z);
		}

		glm::vec4 ConvertPointToHomoCoords(glm::vec3 normalizedCoords)
		{

			return glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
		}

		glm::vec4 ConvertPointToViewCoords(glm::vec4 homogeneousCoords, glm::mat4 projectionMatrix)
		{
			glm::vec4 rayEyeCoords = glm::inverse(projectionMatrix) * homogeneousCoords;

			return glm::vec4(rayEyeCoords.x, rayEyeCoords.y, -1.0f, 0.0f);
		}

		glm::vec4 ConvertPointToWorldCoords(glm::vec4 viewCoords, glm::mat4 viewMatrix)
		{
			glm::vec4 rayWorldCoords = glm::inverse(viewMatrix) * viewCoords;

			return glm::normalize(rayWorldCoords);
		}

		glm::vec4 ConvertNormalizedCoordsToWorldCoords(glm::vec3 normalizedCoords, glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
		{
			glm::vec4 homogeneousCoords = ConvertPointToHomoCoords(normalizedCoords);
			glm::vec4 viewCoords = ConvertPointToViewCoords(homogeneousCoords, projectionMatrix);
			glm::vec4 worldCoords = ConvertPointToWorldCoords(viewCoords, viewMatrix);

			return worldCoords;
		}


	}
}

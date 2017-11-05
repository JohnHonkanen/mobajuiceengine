#include "RayCast.h"


namespace Engine {
	RayCast::RayCast()
	{
	}


	RayCast::~RayCast()
	{
	}

	float RayCast::getRayAngle(float currentRayAngle)
	{
		return currentRayAngle;
	}

	float RayCast::getRayLength(float rayLength)
	{
		return rayLength;
	}

	glm::vec3 RayCast::getP1Posi(glm::vec3 p1Pos)
	{
		// set as camera position

		p1Pos = Camera::mainCamera->transform->GetPosition();
		return p1PoS;
	}

	glm::vec3 RayCast::getP2Posi(glm::vec3 p2Pos)
	{
		// Position of collision
		p2Pos = getP1Posi(p1PoS) + getRayLength(rayLength) * glm::vec3((sinf(currentRayAngle)), cosf(currentRayAngle), 0.0f);
		return p2Pos;
	}
}

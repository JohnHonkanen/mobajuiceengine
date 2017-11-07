#include "RayCast.h"
#include "..\Component\Camera.h"

namespace Engine {
	RayCast::RayCast(float output, float input)
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

	glm::vec2 RayCast::getP1Posi(glm::vec2 p1Pos)
	{
		// set as camera position

		p1Pos = Camera::mainCamera->transform->GetPosition();
		return p1PoS;
	}

	glm::vec2 RayCast::getP2Posi(glm::vec2 p2Pos)
	{
		// Position of collision
		p2Pos = getP1Posi(p1PoS) + getRayLength(rayLength) * glm::vec2((sinf(currentRayAngle)), cosf(currentRayAngle));
		return p2Pos;
	}
}

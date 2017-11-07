#include "RayCast.h"
#include "..\Component\Camera.h"

namespace Engine {
	RayCast::RayCast()
	{
	}


	RayCast::~RayCast()
	{
	}

	RayCast::RayCast(glm::vec3 startPoint)
	{
		point1 = startPoint;
	}

}

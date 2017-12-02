#include "physics/RayCast.h"
#include "components\Camera.h"

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

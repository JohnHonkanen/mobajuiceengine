#pragma once
#include <glm\glm.hpp>
#include "Component\Camera.h"

using namespace std;

namespace Engine {
	class RayCast
	{
	private:

		bool isColision = false;
		float rayLength = 10.0f;

		glm::vec3 p1PoS; // Point 1 Position <--- The camera
		glm::vec3 p2Pos; // Point 2 Position <--- Intersection 

		double curTime = 0; // Time of current frame
		double prevTime = 0; // Time of previous frame
		double currentRayAngle = 0;

	public:
		RayCast();
		~RayCast();

		float getRayAngle(float currentRayAngle);
		float getRayLength(float rayLength);

		glm::vec3 getP1Posi(glm::vec3 p1Pos); // Position of point1 is at Camera position.
		glm::vec3 getP2Posi(glm::vec3 p2Pos); // Position of intersection
	};
}


#pragma once
#include <glm\glm.hpp>


using namespace std;

namespace Engine {
	class RayCast
	{
	private:

		bool isColision = false;
		float rayLength = 10.0f;
		float maxFraction; // Specifies how far along the ray should be checked for an intersection.
		float currentRayAngle = 0;

		glm::vec2 p1PoS; // Point 1 Position <--- The camera
		glm::vec2 p2Pos; // Point 2 Position <--- Intersection 
		glm::vec2 normal; 

		double curTime = 0; // Time of current frame
		double prevTime = 0; // Time of previous frame

	public:
		RayCast(float output, float input);
		~RayCast();

		float getRayAngle(float currentRayAngle);
		float getRayLength(float rayLength);

		glm::vec2 getP1Posi(glm::vec2 p1Pos); // Position of point1 is at Camera position.
		glm::vec2 getP2Posi(glm::vec2 p2Pos); // Position of intersection
	};
}


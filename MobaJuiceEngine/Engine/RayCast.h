#pragma once
#include <glm\glm.hpp>


using namespace std;

namespace Engine {
	class RayCast
	{
	private:

		bool isColision = false;
		int rayDirX;
		float rayLength;
		float currentRayAngle;


		glm::vec3 p1PoS; // Point 1 Position
		glm::vec3 p2Pos; // Point 2 Position

	public:
		RayCast();
		~RayCast();

		float getRayAngle(float currentRayAngle);
		float getRayLength(float rayLength);

		float getP1Posi(glm::vec3 p1Pos);
		float getP2Posi(glm::vec3 p2Pos);
	};
}


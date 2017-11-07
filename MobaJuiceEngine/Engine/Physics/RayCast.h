#pragma once
#include <glm\glm.hpp>
#include <SDL.h>

using namespace std;

namespace Engine {
	class RayCast
	{
	private:
		glm::vec3 point1;


	public:
		RayCast();
		~RayCast();

		RayCast(glm::vec3 startPoint);
	};
}


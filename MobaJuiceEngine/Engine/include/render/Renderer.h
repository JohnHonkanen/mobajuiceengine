/*
	Abstract Renderer
	Dev: John Honkanen
*/
#pragma once
#include <vector>
namespace Engine {
	class Renderer
	{
	public:
		virtual void Render(std::vector<class GameObject*> objects) = 0;
	};
}



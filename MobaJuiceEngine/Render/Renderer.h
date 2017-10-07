/*
	Abstract Renderer
	Dev: John Honkanen
*/
#pragma once
namespace Render {
	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		virtual void render() = 0;
	};
}



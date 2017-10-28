/*
	Window Interface template
	Dev: John Honkanen (B00291253)
*/
#pragma once
namespace Engine {
	class Window {
	public:
		//Initialize the Window
		virtual void Initialize() = 0;
		//Swap Window Buffers for Double buffer implementation
		virtual void SwapBuffers() = 0;
		//Deallocate Memory
		virtual void Destroy() = 0;
	};
}
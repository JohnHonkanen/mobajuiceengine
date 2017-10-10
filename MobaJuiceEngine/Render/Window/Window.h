/*
	Window Interface template
	Dev: John Honkanen (B00291253)
*/
#pragma once

class Window {
public:
	virtual void Initialize() = 0;
	virtual void SwapBuffers() = 0;
	virtual void Destroy() = 0;
};
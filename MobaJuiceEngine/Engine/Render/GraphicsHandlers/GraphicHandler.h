/*
	GraphicsHandler Interface for the program to apply appropriate graphics calls.
	Dev: John Honkanen (B00291253)
*/
#pragma once
class GraphicHandler {
public:
	//Sets up and initialize the Graphics
	virtual void Initialize() = 0;
	//Called at the Start of Every Frame of the Graphics Loop
	virtual void Start() = 0;
	//Called at the End of Every Frame of the Graphics Loop
	virtual void End() = 0;
	//Called when the Graphics memory is destroyed.
	virtual void Destroy() = 0;
};
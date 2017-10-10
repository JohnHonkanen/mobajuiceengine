/*
	GraphicsHandler Interface for the program to apply appropriate graphics calls.
	Dev: John Honkanen (B00291253)
*/
#pragma once
class GraphicHandler {
public:
	virtual void Initialize() = 0;
	virtual void Start() = 0;
	virtual void End() = 0;
	virtual void Destroy() = 0;
};
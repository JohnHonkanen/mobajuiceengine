/*
	Components are behaviours for the GameObject classes.
	Dev: John Honkanen
*/
#pragma once
#include <memory>
//Predefinition of a the GameObject Class
class GameObject;
class Component
{
public:
	Component();
	~Component();
	//Only Called Once per Startup Instance of Class
	virtual void Start() {};
	//Logic Loop
	virtual void Update() {};
	//Rendering Loop
	virtual void Draw() {};

	std::shared_ptr<GameObject> gameObject;
};


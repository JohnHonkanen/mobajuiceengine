#pragma once
#include "Component.h"
class Behaviour :
	public Component
{
public:
	Behaviour(std::string name) : Component(name) {};
	~Behaviour();
	//Only Called Once per Startup Instance of Class
	virtual void Start() {};
	//Logic Loop
	virtual void Update() {};
	//Rendering Loop
	virtual void Draw() {};
	bool isEnabled;
};


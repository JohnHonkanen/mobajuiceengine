#pragma once
#include "Component.h"
class Behaviour :
	public Component
{
public:
	Behaviour(std::string name) : Component(name) {};
	~Behaviour();
	bool isEnabled;
};


/*
	Components are behaviours for the GameObject classes.
	Dev: John Honkanen
*/
#pragma once
#include <memory>
#include <string>
//Predefinition of a the GameObject Class
class GameObject;
class Transform;

class Component
{
public:
	Component();
	Component(std::string name) : name(name) {};
	~Component();
	//Only Called Once per Startup Instance of Class
	virtual void Start() {};
	//Logic Loop
	virtual void Update() {};
	//Rendering Loop
	virtual void Draw() {};

	virtual void SetGameObject(std::shared_ptr<GameObject> gameObject);
	std::weak_ptr<GameObject> gameObject;
	std::shared_ptr<Transform> transform;
	std::string name;
};


/*
	GameObject Class using a Composite of Component classes.
	Dev: John Honkanen
*/
#pragma once
#include <vector>
#include <memory>
#include <cereal\types\vector.hpp>
#include "Transform.h"
class Component;

class GameObject : std::enable_shared_from_this<GameObject>
{
public:
	GameObject();
	~GameObject();
	void AddComponent(std::shared_ptr<Component> component);
	template<class T>
	std::shared_ptr<T> GetComponent();

	template<class Archive>
	void serialize(Archive & archive);

	Transform transform;
	int id;
	std::string name;
	
	std::vector<std::shared_ptr<Component>> components;
};

//Loops Through the Component vector, and returns the first Component of same type if found.
template<class T>
inline std::shared_ptr<T> GameObject::GetComponent()
{
	bool found = false;
	std::unique_ptr<T> component = nullptr;
	int i = 0;

	while (!found) {

		//Checks if we have found Component
		if (component = dynamic_cast<T*>(components[i]))
			found = true;

		i++;
		//Reached the end
		if (i == components.size())
			found = true;
	}
	return component;
}

//Serialization of Components onto a file if component have a serialize method
template<class Archive>
inline void GameObject::serialize(Archive & archive)
{
	archive(components);
}
/*
	GameObject Class using a Composite of Component classes.
	Dev: John Honkanen
*/
#pragma once
#include <vector>
#include <memory>
#include <cereal\types\vector.hpp>
#include "Transform.h"

namespace Engine {
	class Component;
	typedef std::unique_ptr<Component> ComponentUP;
	class GameObject : std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject();
		~GameObject();
		void Update();
		void Draw();
		/*
			Add a Component and gives the GameObject a Sole Ownership of the component
		*/
		void AddComponent(Component *component);
		//Get the first component of the type
		template<class T>
		T* GetComponent();
		//Serialization method
		template<class Archive>
		void serialize(Archive & archive);

		std::unique_ptr<Transform> transform;
		int id;
		std::string name = "";

		std::vector<ComponentUP> components;
	};

	//Loops Through the Component vector, and returns the first Component of same type if found.
	template<class T>
	inline T* GameObject::GetComponent()
	{
		bool found = false;
		T* component = nullptr;
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
}
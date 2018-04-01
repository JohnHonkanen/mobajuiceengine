/*
	GameObject Class using a Composite of Component classes.
	Dev: John Honkanen
*/
#pragma once
#include <vector>
#include <memory>
#include <cereal\cereal.hpp>
#include <cereal\types\vector.hpp>
#include "Transform.h"
#include "../components/Component.h"
#include "render\Material.h"

namespace Engine {
	typedef std::unique_ptr<Component> ComponentUP;

	enum RenderMode {
		FORWARD,
		DEFERRED,
		SHADOW,
	};
	class GameObject : std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject();
		GameObject(std::string name);
		~GameObject();
		void OnLoad();
		void Start();
		void Input();
		void Update(double dt);
		void Draw();

		/* Create a copy of the Gameobject. */
		GameObject * Instantiate();

		GameObject *Instantiate(vec3 position, vec3 rotation);
		/*
			Add a Component and gives the GameObject a Sole Ownership of the component
		*/
		void AddComponent(Component *component);
		void Destroy();
		//Get the first component of the type
		template<class T>
		T* GetComponent();
		//Serialization method

		std::unique_ptr<Transform> transform;
		int id;
		std::string name = "";
		bool enabled = true;
		Material *material;
		class MeshRenderer* meshRenderer = nullptr;
		unsigned int shader;
		string shaderName;
		RenderMode GetRenderMode() const;
		void SetRenderMode(RenderMode mode);

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(name), CEREAL_NVP(transform), CEREAL_NVP(components), CEREAL_NVP(enabled));
		}
	private:
		std::vector<ComponentUP> components;
		RenderMode renderMode;

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
			if (component = dynamic_cast<T*>(components[i].get()))
				found = true;

			i++;
			//Reached the end
			if (i == components.size())
				found = true;
		}
		return component;
	}
}
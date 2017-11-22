/*
	Game Object manager class used for managing game objects. Provides calls that propagate to all gameObjects
*/
#pragma once
#include <memory>
#include <map>
#include <cereal\cereal.hpp>
#include <cereal\types\map.hpp>
#include "GameObject.h"
namespace Engine {
	typedef std::unique_ptr<GameObject> GameObjUniqPtr;

	class GameObjectManager
	{
	public:
		GameObjectManager();
		~GameObjectManager();

		void OnLoad();
		/*
			Calls the update functions for all GameObjects in the manager
		*/
		void Update();
		/*
			Calls the draw functions for all GameObjects in the manager
		*/
		void Draw();

		/*
			Registers and gives ownership of the gameObject to the Manager
			@param gameObject	GameObject that gives the ownership
		*/
		void RegisterGameObject(GameObject * gameObject);
		/*
			Deregister the GameObject with this name, and release ownership
			@param name		Name of the gameObject
			@return			Return the gameObject released. (Needs to be deleted somewhere)
		*/
		GameObject * DeregisterGameObject(std::string name);
		/*
			Factory method to create a game object and automatically register it to the Game Object Manager
			@param name	Name of the gameObject
		*/
		GameObject *createGameObject(std::string name);
		/*
			Find the GameObject with this name
			@param name	Name of the gameObject
		*/
		GameObject * Find(std::string name);

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(gameObjects));
		}
	private:
		std::map<std::string, GameObjUniqPtr> gameObjects;
	};
}
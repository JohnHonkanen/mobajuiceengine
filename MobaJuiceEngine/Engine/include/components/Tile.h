#pragma once
#include <glm\glm.hpp>
#include "components/Component.h"
#include "core/GameObject.h"
#include <cereal\cereal.hpp>
#include <cereal\types\polymorphic.hpp>
#include "Behaviour.h"
#include <vector>


using namespace std;
using namespace glm;

namespace Engine {
	class Tile : public Component{
	private:
		//Size of the overall grid (x,z)
		int gridWidth;
		int gridHeight;
		//Size of an individual grid cell (x,z)
		float cellSize;
		//Initial height of game world plane (y)
		float planeHeight;
		//Used for generating verticies
		vector<float> verticies;


	public:
		vec3 cell;

		void OnLoad();
		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(gridWidth),CEREAL_NVP(gridHeight),CEREAL_NVP(cellSize), CEREAL_NVP(planeHeight));
		}

		/*
		Allows other components to see what cell is highlighted i.e. GUI
		*/
		/*
		Sets up the Camera and its dependicies. Make the gameObject the owner of this component
		@param gameObject	Object that owns this Behaviour
		@return				The created Tile System gameObject
		*/
		static Tile* Create(GameObject * gameObject, float gWidth, float gHeight, float cSize, float pHeight);
		void Copy(GameObject *copyObject) {};
		/*default constructor*/
		Tile();
		/*destructor*/
		~Tile();
		/*
		Tile system constructor, define tile system size and cell size
		@param gWidth			Width(x) of the desired grid area
		@param gHeight			Length(z) of the desired grid area
		@param cWidth			Width(x) of a grid cell
		@param cHeight			Height(z) of a grid cell
		@param pHeight			Initial height(y) of the grid area
		*/
		Tile(float gWidth, float gHeight, float cSize, float pHeight);
		/*
		Defines what tiles are buildable, possibly read in from file or user defined in main
		@param cell				Needs knowledge of highlighted cell, use GetCell method
		@return					True or false for building
		*/
		virtual bool Buildable(vec3 cell);
	
		void GenerateVertices();

		/*
		Define the cell the mouse is over, takes in mouse position from inputs manager
		@param mousePosition	Uses mouse position in calculation of cell
		@return					Grid cell the mouse is on
		*/
		virtual vec3 GetCell(vec3 mousePosition);
		/*
		Defines where the central snap to position is on a cell, pass in Tile::getCell
		@param cell				Requires cell to set center position for object snapping
		@return					Center of the highlighted tile
		*/
		virtual vec3 GetSnapPos(vec3 cell);
		/**/
		vec3 Tile::GetMouseSnapPos(vec3 mousePosition);

		void GetTileData(int& gridHeight, int& gridWidth, float& cellSize, float& planeHeight, vector<float>& verticies);

	};
}
using namespace Engine;

#include <cereal/archives/xml.hpp>

CEREAL_REGISTER_TYPE(Tile);

//Bind it to the Behaviour
CEREAL_REGISTER_POLYMORPHIC_RELATION(Behaviour, Tile);
#pragma once
#include <glm\glm.hpp>
#include "../Component.h"
#include "../GameObject.h"

using namespace std;
using namespace glm;

namespace Engine {
	class Tile : public Component{
	private:
		//Size of the overall grid (x,z)
		float gridWidth;
		float gridHeight;
		//Size of an individual grid cell (x,z)
		float cellWidth;
		float cellHeight;
		//Initial height of game world plane (y)
		float planeHeight;

	public:
		/*
		Allows other components to see what cell is highlighted i.e. GUI
		*/
		vec3 cell;
		/*
		Sets up the Camera and its dependicies. Make the gameObject the owner of this component
		@param gameObject	Object that owns this Behaviour
		@return				The created Tile System gameObject
		*/
		static Tile* Create(GameObject *gameObject);
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
		Tile(float gWidth, float gHeight, float cWidth, float cHeight, float pHeight);
		/*
		Defines what tiles are buildable, possibly read in from file or user defined in main
		@param cell				Needs knowledge of highlighted cell, use GetCell method
		@return					True or false for building
		*/
		bool Buildable(vec3 cell);
		/*
		Draw the highlighted tile, not currently used
		*/
		void Draw(vec2 position);
		/*
		Define the cell the mouse is over, takes in mouse position from inputs manager
		@param mousePosition	Uses mouse position in calculation of cell
		@return					Grid cell the mouse is on
		*/
		vec3 GetCell(vec2 mousePosition);
		/*
		Defines where the central snap to position is on a cell, pass in Tile::getCell
		@param cell				Requires cell to set center position for object snapping
		@return					Center of the highlighted tile
		*/
		vec3 GetSnapPos(vec3 cell);

	};
}
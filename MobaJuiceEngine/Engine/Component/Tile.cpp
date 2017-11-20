#include"Tile.h"
#include "../InputManager.h"

namespace Engine {
	Tile::Tile()
	{

	}

	Tile::~Tile()
	{

	}

	Tile::Tile(float gWidth, float gHeight, float cWidth, float cHeight, float pHeight)
	{
		gridWidth = gWidth;
		gridHeight = gHeight;
		cellWidth = cWidth;
		cellHeight = cHeight;
		planeHeight = pHeight;
	}

	Tile * Tile::Create(GameObject * gameObject, float gWidth, float gHeight, float cWidth, float cHeight, float pHeight)
	{
		Tile *t = new Tile( gWidth,  gHeight,  cWidth,  cHeight,  pHeight);
		gameObject->AddComponent(t);
		return t;
	}

	/*Will change based on defined buildable area, for now stops player building outside of playzone*/
	bool Tile::Buildable(vec3 cell) {
		if ((cell.x >= 0 && cell.x <= gridWidth) && (cell.z >= 0 && cell.z <= gridHeight)) {
			return  true;
		}
		else {
			return false;
		}
	}

	vec3 Tile::GetCell(vec3 mousePosition)
	{								
		cell.x = int(mousePosition.x / cellWidth);		//Stores mouse cell position
		cell.y = planeHeight;
		cell.z = int(mousePosition.y/ cellHeight);
		return cell;
	}

	void Tile::Draw(vec2 position) {
		//Currently not used for anything
	}

	vec3 Tile::GetSnapPos(vec3 cell) {
		vec3 snapPos = vec3(cell.x*cellWidth + (cellWidth / 2.0f), 1.0f, cell.z*cellHeight + (cellHeight / 2.0f));
		return snapPos;
	}

	vec3 Tile::GetMouseSnapPos(vec3 mousePosition) {
		vec3 cell = GetCell(mousePosition);
		return GetSnapPos(cell);
	}
}

//http://www.cplusplus.com/forum/general/18315/
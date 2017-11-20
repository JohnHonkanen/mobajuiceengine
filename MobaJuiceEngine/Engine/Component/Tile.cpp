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

	Tile * Tile::Create(GameObject * gameObject)
	{
		Tile *t = new Tile();
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

	vec3 Tile::GetCell(vec2 mousePosition)
	{								
		cell.x = mousePosition.x / cellWidth;		//Stores mouse cell position
		cell.y = planeHeight+0.1f;
		cell.z = mousePosition.y/ cellHeight;;
		return cell;
	}

	void Tile::Draw(vec2 position) {
		//Currently not used for anything
	}

	vec3 Tile::GetSnapPos(vec3 cell) {
		vec3 snapPos = vec3(cell.x*cellWidth + (cellWidth / 2.0f), 1.0f, cell.z*cellHeight + (cellHeight / 2.0f));
		return snapPos;
	}
}

//http://www.cplusplus.com/forum/general/18315/
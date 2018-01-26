#include "components\Tile.h"
#include "core/InputManager.h"

namespace Engine {
	Tile::Tile() {}

	Tile::~Tile() {}

	Tile::Tile(float gWidth, float gHeight, float cSize, float pHeight)
	{
		gridWidth = gWidth;
		gridHeight = gHeight;
		cellSize = cSize;
		planeHeight = pHeight;
	}

	Tile * Tile::Create(GameObject * gameObject, float gWidth, float gHeight, float cSize, float pHeight)
	{
		Tile *t = new Tile( gWidth,  gHeight, cSize,  pHeight);
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

	void Tile::GenerateVertices() {

		for (float x = 0; x <= gridWidth; x++) {
			verticies.push_back(x * cellSize);
			verticies.push_back(planeHeight);
			verticies.push_back(0);

			verticies.push_back(x * cellSize);
			verticies.push_back(planeHeight);
			verticies.push_back(gridHeight * cellSize);
		}
		for (float z = 0; z <= gridHeight; z++) {
			verticies.push_back(0);
			verticies.push_back(planeHeight);
			verticies.push_back(z * cellSize);

			verticies.push_back(gridWidth * cellSize);
			verticies.push_back(planeHeight);
			verticies.push_back(z * cellSize);
		}
	}

	void Tile::OnLoad()
	{
		GenerateVertices();
	}

	vec3 Tile::GetCell(vec3 mousePosition)
	{								
		cell.x = int(mousePosition.x / cellSize);		//Stores mouse cell position
		cell.y = planeHeight;
		cell.z = int(mousePosition.z/ cellSize);
		return cell;
	}

	vec3 Tile::GetSnapPos(vec3 cell) {
		vec3 snapPos = vec3(cell.x*cellSize, cell.y, cell.z*cellSize);
		return snapPos;
	}

	vec3 Tile::GetMouseSnapPos(vec3 mousePosition) {
		vec3 cell = GetCell(mousePosition);
		return GetSnapPos(cell);
	}
	void Tile::GetTileData(int & gridHeight, int & gridWidth, float & cellSize, float & planeHeight, vector<float>& verticies)
	{
		gridHeight = Tile::gridHeight;
		gridWidth = Tile::gridWidth;
		cellSize = Tile::cellSize;
		planeHeight = Tile::planeHeight;
		verticies = Tile::verticies;
	}

}

//http://www.cplusplus.com/forum/general/18315/
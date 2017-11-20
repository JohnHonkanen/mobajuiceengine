#include <catch.hpp>
#include "../MobaJuiceEngine/Engine/Component/Tile.cpp"
#include <glm\glm.hpp>

using namespace Engine;
using namespace glm;

TEST_CASE("Tile system test", "[Tile]") {
	Tile tile = Tile(100, 100, 10, 10, 0);
	SECTION("GetCell()") {
		vec3 cell = tile.GetCell(vec3(50, 0, 50));
		REQUIRE(cell.x == 5);
		REQUIRE(cell.y == 0);
		REQUIRE(cell.z == 5);
		cell = tile.GetCell(vec3(400, 0, 10));
		REQUIRE(cell.x == 40);
		REQUIRE(cell.y == 0);
		REQUIRE(cell.z == 1);
	}

	SECTION("GetSnapPos()") {
		vec3 cell = vec3(5, 0, 5);
		vec3 snapPos = tile.GetSnapPos(cell);
		REQUIRE(snapPos.x == 50);
		REQUIRE(snapPos.y == 0);
		REQUIRE(snapPos.z == 50);
	}
	SECTION("Buildable()") {
		vec3 cell = vec3(5, 0, 5);
		bool pass = tile.Buildable(cell);
		REQUIRE(pass==true);
		cell = vec3(500, 0, 350);
		pass = tile.Buildable(cell);
		REQUIRE(pass == false);
	}
	/*SECTION("GetSnapPos()") {
		vec3 cell = vec3(5, 0, 5);
		vec3 snapPos = tile.GetSnapPos(cell);
		REQUIRE(snapPos.x == 55);
		REQUIRE(snapPos.y == 0);
		REQUIRE(snapPos.z == 55);
	}*/
}

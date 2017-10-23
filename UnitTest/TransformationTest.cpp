#include "catch.hpp"
#include "..\MobaJuiceEngine\Transform.cpp"

TEST_CASE("Transformation Direction calculation", "[Transform]") {
	Transform transform = Transform();
	
	SECTION("Transform::Front()") {
		transform.SetEulerAngle(vec3(0.f, 90.0f, 0.0f));
		vec3 front = transform.Front();

		REQUIRE(front.x == Approx(1.0f));
		REQUIRE(front.y == Approx(0.0f));
		REQUIRE(front.z == Approx(0.0f));

		transform.SetEulerAngle(vec3(0.f, 45.0f, 0.0f));
		front = transform.Front();
		REQUIRE(front.x == Approx(0.70711f));
		REQUIRE(front.y == Approx(0.0f));
		REQUIRE(front.z == Approx(0.70711f));
	}
	SECTION("Transform::Up()") {
		transform.SetEulerAngle(vec3(0.f, 90.0f, 0.0f));
		vec3 up = transform.Up();

		REQUIRE(up.x == Approx(0.0f));
		REQUIRE(up.y == Approx(1.0f));
		REQUIRE(up.z == Approx(0.0f));

		transform.SetEulerAngle(vec3(90.f, 0.0f, 0.0f));

		up = transform.Up();

		REQUIRE(up.x == Approx(0.0f));
		REQUIRE(up.y == Approx(0.0f));
		REQUIRE(up.z == Approx(1.0f));
		
	}
	SECTION("Transform::Right()") {
		transform.SetEulerAngle(vec3(0.f, 90.0f, 0.0f));
		vec3 right = transform.Right();

		REQUIRE(right.x == Approx(0.0f));
		REQUIRE(right.y == Approx(0.0f));
		REQUIRE(right.z == Approx(-1.0f));
	}
}
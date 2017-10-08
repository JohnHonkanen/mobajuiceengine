#include "catch.hpp"
#include "../MobaJuiceEngine/Dictionary.h"

TEST_CASE("Dictionary Save and Get", "[factorial]") {
	Dictionary<int> dict;
	dict.SaveWithObject("number1", 1);
	REQUIRE(dict.Get("number1") == 1);

	Dictionary<std::string> stringDict;
	stringDict.SaveWithObject("number1", "hello");
	REQUIRE(stringDict.Get("number1") == "hello");
}
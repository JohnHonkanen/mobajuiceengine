#include "catch.hpp"
#include "../MobaJuiceEngine/Dictionary.h"

TEST_CASE("Dictionary Save and Get", "[Dictionary Save Get]") {
	Dictionary<int> dict;
	dict.Save("number1", 1);
	REQUIRE(dict.Get("number1") == 1);

	Dictionary<std::string> stringDict;
	stringDict.Save("number1", "hello");
	REQUIRE(stringDict.Get("number1") == "hello");
}
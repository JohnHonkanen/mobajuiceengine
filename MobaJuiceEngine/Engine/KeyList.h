#pragma once
#include <string>

using namespace std;

namespace Engine{
	class KeyList
{
	KeyList();
		KeyList(string name);
		~KeyList();

		string ID = "";
		int id;

	};
}


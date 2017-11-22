#pragma once
#include <string>

using namespace std;

namespace Engine{
	class KeyList
{
	public:
		KeyList();
		KeyList(string nameID);
		~KeyList();

		string ID = "";
		int keyID;

	private:
	
	};
}


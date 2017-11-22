#pragma once

#include <string>

using namespace std;

namespace Engine {

	class KeyAxis {
	public:
		KeyAxis();
		KeyAxis(string name, string positive, string negative);
		int GetValue();
		void GetKeys(string &positive, string &negative);
		void SetPress(int positivePressed, int negativePressed);

	private:
		string positive, negative;
		string name;
		int value = 0;

		int positivePressed, negativePressed;
	};
}
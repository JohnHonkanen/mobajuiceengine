#pragma once

#include <string>
#include <cereal\cereal.hpp>

using namespace std;

namespace Engine {

	class KeyAxis {
	public:
		KeyAxis();
		KeyAxis(string name, string positive, string negative);
		int GetValue();
		void GetKeys(string &positive, string &negative);
		void SetPress(int positivePressed, int negativePressed);

		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(CEREAL_NVP(name), CEREAL_NVP(positive), CEREAL_NVP(negative));
		}

	private:
		string positive, negative;
		string name;
		int value = 0;

		int positivePressed, negativePressed;
	};
}
#include "render\FontManager.h"
#include <iostream>

using namespace std;

namespace Engine {
	FontManager::FontManager()
	{
		if (TTF_Init() == -1)
		{
			cout << "Unable to load font. :(" << endl;
		}
	}
	FontManager::~FontManager()
	{}

	void FontManager::CreateFont(std::string name)
	{
		font.insert(pair<string, unique_ptr<Font>>(name, make_unique<Font>(name)));
	}

	Font * FontManager::GetFont(std::string name)
	{
		auto it = font.find(name);
		if (it != font.end()) {
			return font[name].get();
		}

		CreateFont(name);
		return font[name].get();
	}


}

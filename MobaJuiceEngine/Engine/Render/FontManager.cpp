#include "FontManager.h"
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
		TTF_Font *f = TTF_OpenFont(name.c_str(), 36);
		font.insert(pair<string, FontShptr>(name, FontShptr(f)));
	}

	TTF_Font * FontManager::GetFont(std::string name)
	{
		auto it = font.find(name);
		if (it != font.end()) {
			return font[name].get();
		}

		CreateFont(name);
		return font[name].get();
	}


}


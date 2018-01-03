#pragma once
#include <SDL_ttf.h>
#include <map>

class Font {
public:
	static Font &Instance() {
		static Font font;
		return font;
	}

	void load(const char* path) {
		ttfPath = path;
		return;
	}

	TTF_Font* getFont(int size) {
		std::map<int, TTF_Font*>::iterator it;
		it = Fonts.find(size);
		if (it != Fonts.end())
			return it->second;
		else {
			TTF_Font* mFont = TTF_OpenFont(ttfPath, size);
			Fonts.insert(std::pair<int, TTF_Font*>(size, mFont));
			return mFont;
		}
	}

private:
	const char* ttfPath;
	std::map<int, TTF_Font*> Fonts;
};
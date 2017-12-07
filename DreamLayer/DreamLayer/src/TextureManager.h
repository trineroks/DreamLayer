#pragma once
#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* loadTexture(const char* file);
	static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
	static void drawSurface(SDL_Surface* surface, int x, int y);
};


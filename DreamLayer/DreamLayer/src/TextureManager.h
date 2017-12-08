#pragma once
#include "Game.h"
#include "TextureRegion.h"

class TextureManager {
public:
	static SDL_Texture* loadTexture(const char* file);
	static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
	static void draw(TextureRegion* textRegion, int x, int y);
	static void drawResized(TextureRegion* textRegion, int x, int y, int w, int h);
	static void drawSurface(SDL_Surface* surface, int x, int y);
};


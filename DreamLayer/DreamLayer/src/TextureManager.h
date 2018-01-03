#pragma once
#include "TextureRegion.h"

class TextureManager {
public:
	static SDL_Texture* loadTexture(const char* file);
	static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
	static void draw(TextureRegion textRegion, int x, int y);
	static void draw(TextureRegion textRegion, int x, int y, double degrees, int rotatex, int rotatey);
	static void draw(TextureRegion textRegion, int x, int y, double degrees, int rotatex, int rotatey, SDL_RendererFlip flip);
	static void drawResized(TextureRegion textRegion, int x, int y, int w, int h);
	static void drawResized(TextureRegion textRegion, int x, int y, int w, int h, double degrees, int rotatex, int rotatey);
	static void drawResized(TextureRegion textRegion, int x, int y, int w, int h, double degrees, int rotatex, int rotatey, SDL_RendererFlip flip);
};


#pragma once
#include "SDL.h"
#include "TextureManager.h"

class Sprite {
public:
	Sprite(const char* path);
	void setTexture(const char* path);
	void update();

	~Sprite();

	int x = 0;
	int y = 0;

private:
	SDL_Texture *texture;
	SDL_Rect src, dest;
};


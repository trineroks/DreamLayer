#pragma once
#include "SDL.h"

class TextureRegion {
public:
	TextureRegion();
	TextureRegion(SDL_Texture* tex, int x, int y, int w, int h);
	~TextureRegion();

	void setRegion(int x, int y, int w, int h);

	SDL_Texture* getTexture() {
		return texture;
	}

	SDL_Rect getRect() {
		return region;
	}

private:
	SDL_Rect region;
	SDL_Texture* texture;

};


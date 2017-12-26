#pragma once
#include "SDL.h"

class TextureRegion {
public:
	TextureRegion();
	TextureRegion(SDL_Texture* tex, int x, int y, int w, int h);
	~TextureRegion();

	SDL_Texture* getTexture() {
		return texture;
	}

	const SDL_Rect getRect() const {
		return region;
	}

private:
	void setRegion(int x, int y, int w, int h);

	SDL_Rect region;
	SDL_Texture* texture;

};


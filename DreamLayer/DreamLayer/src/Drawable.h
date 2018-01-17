#pragma once
#include "TextureRegion.h"
#include "TextureManager.h"


class Drawable {
public:
	Drawable();
	Drawable(TextureRegion &texRegion);
	~Drawable();

	void render();
	void renderStatic();

	float angle = 0.0f;

protected:
	float wscale = 1.0f;
	float hscale = 1.0f;

	SDL_RendererFlip flip;

	int xdraw = 0;
	int ydraw = 0;
	int hdraw = 0;
	int wdraw = 0;

	int xoffset = 0;
	int yoffset = 0;

	TextureRegion* region = nullptr;
};


#pragma once
#include "TextureManager.h"

class TextureRegion;
class Sprite {
public:
	Sprite(TextureRegion *texRegion);
	void update();

	~Sprite();

	int x = 0;
	int y = 0;

	int deltx = 0;
	int delty = 0;

private:
	TextureRegion *region;
};


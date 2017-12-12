#pragma once
#include "TextureManager.h"
#include "Rect.h"

class TextureRegion;
class Sprite {
public:
	Sprite(TextureRegion *texRegion);

	void setPosition(int _x, int _y);
	
	void setCollisionBox(Rect *rect);
	void update();

	~Sprite();

	int x = 0;
	int y = 0;

	int deltx = 0;
	int delty = 0;

	Rect &getRect() {
		return *rect;
	}

private:
	TextureRegion *region;
	Rect *rect;
	
};


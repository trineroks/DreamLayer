#pragma once
#include "TextureManager.h"
#include "Rect.h"
#include "Constants.h"

class TextureRegion;
class Rect;
class Sprite {
public:
	typedef enum {
		TOPLEFT = 0,
		CENTER,
		BOTTOMCENTER,
		CUSTOM
	}PositionType;

	PositionType posType = TOPLEFT;

	Sprite(TextureRegion &texRegion);

	Sprite();

	void setPosition(int _x, int _y);
	
	void setCollisionBox(Rect rect);

	void scaleSprite(int w, int h);
	void scaleSpriteAndCollisionBox(int w, int h);

	void update();
	void render();

	~Sprite();
	
	int xoffset = 0;
	int yoffset = 0;

	int collxOffset = 0;
	int collyOffset = 0;

	float x = 0;
	float y = 0;

	float deltx = 0;
	float delty = 0;

	float angle = 0;

	bool drawDebug = false;

	Rect &getRect() {
		return rect;
	}

private:
	void drawUpdate();

	int wdraw = 0;
	int hdraw = 0;

	int xdraw = 0;
	int ydraw = 0;

	TextureRegion *region;
	Rect rect;
};


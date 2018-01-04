#pragma once
#include "TextureManager.h"
#include "Rect.h"
#include "Constants.h"
#include "Vector2D.h"

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

	Rect getPredictiveX();
	Rect getPredictiveY();

	~Sprite();
	
	int xoffset = 0;
	int yoffset = 0;

	int collxOffset = 0;
	int collyOffset = 0;

	Vector2D pos = Vector2D(0, 0);

	Vector2D prevPos = Vector2D(0, 0);

	Vector2D delta = Vector2D(0, 0);

	float angle = 0;

	bool drawDebug = false;

	Rect &getRect() {
		return rect;
	}

	void revertXPos() {
		pos.x = prevPos.x;
	}

	void revertYPos() {
		pos.y = prevPos.y;
	}

	void revertPos() {
		pos.x = prevPos.x;
		pos.y = prevPos.y;
	}

private:
	int wdraw = 0;
	int hdraw = 0;

	int xdraw = 0;
	int ydraw = 0;

	TextureRegion *region;
	Rect rect;
};


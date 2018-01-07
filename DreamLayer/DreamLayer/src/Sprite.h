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
	}PositionType;

	Sprite(TextureRegion &texRegion);

	Sprite();

	void setPosition(int _x, int _y);
	
	void setCollisionBox(Rect rect);
	void setTextureRegion(TextureRegion &tex);

	void scaleSprite(float w, float h);
	void scale(float w, float h);

	virtual void update();
	void render();

	Rect getPredictiveX();
	Rect getPredictiveY();

	~Sprite();

	/*Custom Orientation Type. From your texture (in pixels), define the point within the texture using x and y 
	that will serve as the center/rotating point. Collision offsets define where in the point the collision box will
	be created. Top left serves as (0,0). For example, a 30(w)x50(h) sprite with a centerpoint at (15,15) with a collision 
	box of 30x30 from the top right will use: (15, 15, 0, 0)
	*/
	void setCustomOrientationType(int _xoffset, int _yoffset, int _collxOffset, int _collyOffset);
	void setOrientationType(PositionType type);

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

protected:
	float wscale = 0.0f;
	float hscale = 0.0f;

	int xoffset = 0;
	int yoffset = 0;

	int collxOffset = 0;
	int collyOffset = 0;

	int wdraw = 0;
	int hdraw = 0;

	int xdraw = 0;
	int ydraw = 0;

	TextureRegion *region;
	Rect rect;
};


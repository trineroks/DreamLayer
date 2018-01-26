#pragma once
#include "TextureManager.h"
#include "Rect.h"
#include "Constants.h"
#include "Vector2D.h"
#include "Drawable.h"

class TextureRegion;
class Rect;
class Sprite : public Drawable {
public:
	typedef enum {
		TOPLEFT = 0,
		CENTER,
		BOTTOMCENTER,
	}PositionType;

	Sprite(TextureRegion &texRegion);

	Sprite();

	//Set position in terms of pixels
	void setPosition(int pixelx, int pixely);
	
	void setCollisionBox(Rect rect);
	void setTextureRegion(TextureRegion &tex);

	void scale(float w, float h);

	virtual void update();
	void render();

	Rect getPredictiveRectX();
	Rect getPredictiveRectY();
	Rect getPredictiveRect();

	~Sprite();

	/*Custom Orientation Type. From your texture (in pixels), define the point within the texture using x and y 
	that will serve as the center/rotating point. Collision offsets define where in the point the collision box will
	be created. Top left serves as (0,0). For example, a 30(w)x50(h) sprite with a centerpoint at (15,15) with a collision 
	box of 30x30 from the top right will use: (15, 15, 0, 0). A collision box of 8x8 around the centerpoint (15,15) would
	yield (15, 15, 11, 11), since 11 pixels inside the texture would be where the top right of the collision box would start.
	*/
	void setCustomOrientationType(int _xoffset, int _yoffset, int _collxOffset, int _collyOffset);
	void setOrientationType(PositionType type);

	Vector2D pos = Vector2D(0, 0);

	Vector2D prevPos = Vector2D(0, 0);

	Vector2D delta = Vector2D(0, 0);

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
		rect.revertPos();
	}

protected:
	int collxOffset = 0;
	int collyOffset = 0;
	Rect rect;
};


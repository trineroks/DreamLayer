#pragma once
#include "TextureManager.h"
#include "SpriteBank.h"

class TextureManager;
class Rect{
public:
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	int prevx = 0;
	int prevy = 0;

	Rect() {}

	Rect(int _x, int _y, int _w, int _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		prevx = x;
		prevy = y;
	}

	void setPos(int _x, int _y) {
		prevx = x;
		prevy = y;
		x = _x;
		y = _y;
	}

	void setDimension(int _w, int _h) {
		w = _w;
		h = _h;
	}

	bool contains(float _x, float _y) {
		return !(_x > x + w || _x < x || _y > y + w || _y < y);
	}

	bool intersects(const Rect &culprit) {
		return !(culprit.x > x + w || culprit.y > y + h || culprit.x + culprit.w < x || culprit.y + culprit.h < y);
	}

	bool collidedFromLeft(const Rect &culprit) {
		if (intersects(culprit))
			return (culprit.prevx + culprit.w < x && culprit.x + culprit.w >= x);
		return false;
	}

	bool collidedFromRight(const Rect &culprit) {
		if (intersects(culprit))
			return (culprit.prevx > x + w && culprit.x <= x + w);
		return false;
	}

	bool collidedFromTop(const Rect &culprit) {
		if (intersects(culprit))
			return (culprit.prevy + culprit.h < y && culprit.y + culprit.h >= y);
		return false;
	}

	bool collidedFromBot(const Rect &culprit) {
		if (intersects(culprit))
			return (culprit.prevy > y + h && culprit.y <= y + h);
		return false;
	}

	void drawDebugBox() {
		if (w != 0 && h != 0)
			TextureManager::drawResized(SpriteBank::Instance().TestCollisionBox, x, y, w, h);
	}
};
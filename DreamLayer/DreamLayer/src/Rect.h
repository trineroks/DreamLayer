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

	float wscale = 1.0f;
	float hscale = 1.0f;

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

	void revertPos() {
		x = prevx;
		y = prevy;
	}

	void revertXPos() {
		x = prevx;
	}

	void revertYPos() {
		y = prevy;
	}

	void setDimension(int _w, int _h) {
		w = _w;
		h = _h;
	}

	bool contains(int _x, int _y) {
		return !(_x > x + (w * wscale) || _x < x || _y > y + (w * wscale) || _y < y);
	}

	bool intersects(const Rect &culprit) {
		return !(culprit.x > x + (w * wscale) || culprit.y > y + (h * hscale) || culprit.x + (culprit.w * culprit.wscale) < x || culprit.y + (culprit.h * culprit.hscale) < y);
	}

	bool collidedFromLeft(const Rect &culprit) {
		if (intersects(culprit))
			return (culprit.prevx + (culprit.w * culprit.wscale) < x && culprit.x + (culprit.w * culprit.wscale) >= x);
		return false;
	}

	bool collidedFromRight(const Rect &culprit) {
		if (intersects(culprit))
			return (culprit.prevx > x + (w * wscale) && culprit.x <= x + (w * wscale));
		return false;
	}

	bool collidedFromTop(const Rect &culprit) {
		if (intersects(culprit))
			return (culprit.prevy + (culprit.h * culprit.hscale) < y && culprit.y + (culprit.h * culprit.hscale) >= y);
		return false;
	}

	bool collidedFromBot(const Rect &culprit) {
		if (intersects(culprit))
			return (culprit.prevy > y + (h * hscale) && culprit.y <= y + (h * hscale));
		return false;
	}

	void drawDebugBox() {
		if (w != 0 && h != 0)
			TextureManager::drawResized(SpriteBank::Instance().TestCollisionBox, x, y, w * wscale, h * hscale);
	}
};
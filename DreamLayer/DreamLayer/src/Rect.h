#pragma once

class Rect{
public:
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	Rect(int _x, int _y, int _w, int _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

	void setPos(int _x, int _y) {
		x = _x;
		y = _y;
	}

	void setDimension(int _w, int _h) {
		w = _w;
		h = _h;
	}

	bool intersects(int _x, int _y) {
		return !(_x > x + w || _x < x || _y > y + w || _y < y);
	}

	bool intersects(const Rect &culprit) {
		return !(culprit.x > x + w || culprit.y > y + h || culprit.x + culprit.w < x || culprit.y + culprit.h < y);
	}
};
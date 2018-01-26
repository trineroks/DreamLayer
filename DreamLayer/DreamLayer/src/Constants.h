#pragma once

const static float FRAMEDELAY = 1000.0f/60.0f;
const static float SPEED = 2.0f;
const static float SECOND = 1000.0f;

const static float MAX_ENTITIES = 5000;
const static float PI = 3.14159265;

const static int MAX_MAP_DIMENSION = 500 * 500;

const static int TILE_PIXELSIZE = 64;
const static int TILE_RENDERSIZE = 64;

const static int WALL_HEIGHT = 128;

namespace CollisionType {
	const char NONE = 0;
	const char VERTICAL = 1;
	const char HORIZONTAL = 2;
	const char CORNER = 3;
}

class Point {
public:
	Point& operator=(const Point &p) {
		this->x = p.x;
		this->y = p.y;

		return *this;
	}

	bool operator==(const Point &p) const {
		return (this->x == p.x && this->y == p.y);
	}

	Point(int _x, int _y) : x(_x), y(_y) {}
	Point() {}

	int x = -1;
	int y = -1;
};

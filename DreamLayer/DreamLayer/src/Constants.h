#pragma once

const static float FRAMEDELAY = 1000.0f/60.0f;
const static float SPEED = 2.0f;
const static float SECOND = 1000.0f;

const static float MAX_ENTITIES = 5000;
const static float PI = 3.14159265;

const static int MAX_MAP_DIMENSION = 256 * 256;

const static int TILE_PIXELSIZE = 64;

namespace CollisionType {
	const char NONE = 0;
	const char VERTICAL = 1;
	const char HORIZONTAL = 2;
	const char CORNER = 3;
}

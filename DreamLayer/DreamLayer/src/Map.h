#pragma once
#include "Constants.h"
#include "Tile.h"
#include "Rect.h"
#include "Terrain.h"
#include "Sprite.h"
#include <bitset>
#include <vector>

class Map {
public:
	Map();
	~Map();

	void generate();
	void generateCollisionMap();
	void render();

	bool isCollidingPredict(Sprite* sprite);
	bool isColliding(Sprite* sprite);

	char isCollidingWithType(Sprite* sprite);

	bool testCollideDirection(Sprite* sprite);

	void clearMap();

	void editTerrainAt(int _x, int _y, int tile);

	bool drawDebug = false;
private:
	bool rowIsObstacle(int x, int y, int length, std::bitset<MAX_MAP_DIMENSION>* bset);
	//Using pixel coordinates, return the terrain at this specified area.
	Terrain* getTerrainAt(int _x, int _y);

	Terrain terrains[MAX_MAP_DIMENSION];
	std::vector<Rect> collisionMap;
	//Locations (simple variable sized rect), Enemies
	int w, h;
	short terrainW, terrainH;
};


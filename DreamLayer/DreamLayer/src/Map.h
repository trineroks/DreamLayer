#pragma once
#include "Constants.h"
#include "ShadowCast.h"
#include "Tile.h"
#include "Rect.h"
#include "Terrain.h"
#include "Sprite.h"
#include "Character.h"
#include <bitset>
#include <vector>

class Character;
class Map {
public:
	Map();
	~Map();

	void addPlayer(Character &player) {
		chr = &player;
	}

	void generate();
	void generateCollisionMap();
	void update();
	void render();

	bool isCollidingPredict(Sprite* sprite);
	bool isColliding(Sprite* sprite);

	char isCollidingWithType(Sprite* sprite);

	bool testCollideDirection(Sprite* sprite);

	void clearMap();

	void editTerrainAt(int _x, int _y, int tile);

	//Using pixel coordinates, return the map coordinate at this area.
	Point getPositionInMap(int pixelx, int pixely);

	//Using map coordinates, return the pixel coordinate of this area.
	Point getPixelPositionInMap(int _x, int _y);

	//Using pixel coordinates, return the terrain at this specified area.
	Terrain* getTerrainAt(int pixelx, int pixely);

	Terrain* getTerrainAtTerrains(int _x, int _y);
	Terrain* getTerrainAtTerrains(Point &p);

	int getWidth() {
		return w;
	}

	int getHeight() {
		return h;
	}

	bool drawDebug = false;
private:
	bool rowIsObstacle(int x, int y, int length, std::bitset<MAX_MAP_DIMENSION>* bset);
	void getScannableTerrains();

	Terrain terrains[MAX_MAP_DIMENSION];
	ShadowCast shadowEngine;

	std::vector<Rect> collisionMap;
	//Locations (simple variable sized rect), Enemies
	int w, h;
	short terrainW, terrainH;

	Point checkStart = Point(0, 0);
	Point checkEnd = Point(0, 0);

	Character* chr;
};


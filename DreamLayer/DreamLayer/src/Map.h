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
#include "Serializable.h"

class Character;
class Map : public Serializable {
public:
	Map();
	~Map();

	void addPlayer(Character &player) {
		chr = &player;
	}

	void save(BinSerializer* b) override;
	void load(BinReader* b) override;

	void generate();
	void update(float delta);
	void render(float delta);
	void renderWallLayer(float delta);
	void renderFogLayer();
	bool tileIsObstacle(int pixelx, int pixely);
	bool tileIsObstacle(Point pixel);

	bool isTileTraversableAI(Point start, Point end, Sprite &sprite);

	bool willCollideHandle(Sprite* sprite);
	bool isColliding(Rect collBox);

	void clearMap();

	void editTerrainAt(int pixelx, int pixely, int tile);

	//Using pixel coordinates, return the map coordinate at this area.
	Point getPositionInMap(int pixelx, int pixely);

	//Using pixel coordinates, return the lightmap coordinate at this area.
	Point getPositionInLightMap(int pixelx, int pixely);

	//Using map coordinates, return the pixel coordinate of this area. Pixel coordinate
	//will be centered in the square.
	Point getPixelPositionInMap(int _x, int _y);

	//Using pixel coordinates, return the terrain at this specified area.
	Terrain* getTerrainAt(int pixelx, int pixely);

	Terrain* getTerrainAtTerrains(int _x, int _y);
	Terrain* getTerrainAtTerrains(Point &p);

	const int getWidth() const {
		return w;
	}

	const int getHeight() const {
		return h;
	}

	int getLightMapW() {
		return lightMapW;
	}

	int getLightMapH() {
		return lightMapH;
	}

	bool getLightMapValueAt(int x, int y) {
		return lightMap[(y * lightMapW) + x];
	}

	void setVisibilityAt(int x, int y) {
		visibilityMap.set((y * lightMapW) + x);
	}
	bool drawDebug = false;
private:
	void getScannableTerrains();

	void drawWall(int drawX, int drawY, int mapX, int mapY, Terrain &t, float delta);

	Terrain terrains[MAX_MAP_DIMENSION];
	std::bitset<MAX_MAP_DIMENSION * 16> lightMap;
	std::bitset<MAX_MAP_DIMENSION * 16> visibilityMap;
	int lightMapW, lightMapH;

	ShadowCast shadowEngine;

	//Locations (simple variable sized rect), Enemies
	int w, h;
	short terrainW, terrainH;

	Point checkStart = Point(0, 0);
	Point checkEnd = Point(0, 0);

	Character* chr;
};


#include "Map.h"
#include "TextureManager.h"
#include "SpriteBank.h"
#include "Constants.h"


Map::Map() {
	w = 30;
	h = 30;
	terrainW = TILE_PIXELSIZE;
	terrainH = TILE_PIXELSIZE;
}

Map::~Map() {
}

Terrain* Map::getTerrainAt(int _x, int _y){
	int x = (_x + terrainW/2) / terrainW;
	int y = (_y + terrainH/2) / terrainH;
	int index = (y * w) + x;
	if (index >= MAX_MAP_DIMENSION || index < 0)
		return nullptr;
	return &terrains[index];
}

void Map::generate() {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			Terrain terrain = Terrain(terrainW, terrainH);
			terrain.setTile(Tile::grass);
			terrain.setPosition(x, y);
			terrains[(y * w) + x] = terrain;
		}
	}
	generateCollisionMap();
}

void Map::clearMap() {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			terrains[(y * w) + x].setTile(Tile::grass);
		}
	}
	generateCollisionMap();
}

void Map::generateCollisionMap() {
	collisionMap.clear();
	std::bitset<MAX_MAP_DIMENSION> visited;
	int index = 0;
	int collx = 0;
	int colly = 0;
	int collw = 0;
	int collh = 0;
	int xlen = 0;
	int ylen = 0;
	int collIndex = 0;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			index = (y * w) + x;
			if (terrains[index].obstacle && visited[index] == 0) {
				Terrain t = terrains[index];
				visited.set(index);
				collx = t.getDrawX();
				colly = t.getDrawY();
				int dx = x+1;
				xlen = 1;
				while (dx < w && terrains[(y * w) + dx].obstacle && visited[(y * w) + dx] == 0) {
					visited.set((y * w) + dx);
					dx++;
					xlen++;
				}
				collw = terrainW * xlen;;
				int dy = y + 1;
				ylen = 1;
				while (dy < h && rowIsObstacle(x, dy, xlen, &visited)) {
					ylen++;
					dy++;
				}
				collh = terrainH * ylen;
				collisionMap.emplace_back(Rect(collx, colly, collw, collh));
				collIndex++;
				x = dx;
			}
		}
	}
}

bool Map::rowIsObstacle(int x, int y, int length, std::bitset<MAX_MAP_DIMENSION>* bset) {
	for (int i = 0; i < length; i++) {
		int index = (y * w) + x + i;
		if (!terrains[index].obstacle)
			return false;
	}
	for (int i = 0; i < length; i++) {
		int index = (y * w) + x + i;
		bset->set(index);
	}
	return true;
}

void Map::editTerrainAt(int _x, int _y, int tile) {
	Terrain* t = getTerrainAt(_x, _y);
	t->setTile(tile);
	generateCollisionMap();
}

bool Map::isCollidingPredict(Sprite* sprite) {
	Rect rx = sprite->getPredictiveX();
	Rect ry = sprite->getPredictiveY();
	bool ret = false;
	for (int i = 0; i < collisionMap.size(); i++) {
		if (collisionMap[i].intersects(rx)) {
			//printf("Collision!!\n");
			sprite->revertXPos();
			ret = true;
		}
		if (collisionMap[i].intersects(ry)) {
			//printf("Collision!!\n");
			sprite->revertYPos();
			ret = true;
		}
	}
	//printf("\n");
	return ret;
}

bool Map::testCollideDirection(Sprite* sprite) {
	Rect r = sprite->getRect();
	Rect col;
	bool ret = false;
	for (int i = 0; i < collisionMap.size(); i++) {
		col = collisionMap[i];
		if (col.collidedFromBot(r)) {
			printf("Collided from Bottom!\n");
			ret = true;
		}
		if (col.collidedFromTop(r)) {
			printf("Collided from Top!\n");
			ret = true;
		}
		if (col.collidedFromRight(r)) {
			printf("Collided from Right!\n");
			ret = true;
		}
		if (col.collidedFromLeft(r)) {
			printf("Collided from Left!\n");
			ret = true;
		}
	}
	return ret;
}

bool Map::isColliding(Sprite* sprite) {
	Rect r = sprite->getRect();
	for (int i = 0; i < collisionMap.size(); i++) {
		if (collisionMap[i].intersects(r))
			return true;
	}
	return false;
}

char Map::isCollidingWithType(Sprite* sprite) {
	Rect r = sprite->getRect();
	char colType = CollisionType::NONE;
	for (int i = 0; i < collisionMap.size(); i++) {
		if (collisionMap[i].collidedFromBot(r) || collisionMap[i].collidedFromTop(r))
			colType = CollisionType::HORIZONTAL;
		if (collisionMap[i].collidedFromRight(r) || collisionMap[i].collidedFromLeft(r)) {
			if (colType == CollisionType::HORIZONTAL)
				colType = CollisionType::CORNER;
			else 
				colType = CollisionType::VERTICAL;
		}
	}
	return colType;
}

void Map::render() {
	for (int i = 0; i < w * h; i++) {
		terrains[i].render();
	}
	if (drawDebug) {
		for (int i = 0; i < collisionMap.size(); i++) {
			collisionMap[i].drawDebugBox();
		}
	}
}

#include "Map.h"
#include "TextureManager.h"
#include "SpriteBank.h"
#include "Constants.h"

Map::Map() {
	w = 60;
	h = 60;
	terrainW = TILE_RENDERSIZE;
	terrainH = TILE_RENDERSIZE;

	shadowEngine.setMap(*this);

	grass = &SpriteBank::Instance().Grass;
	wall = &SpriteBank::Instance().Wall;
	fog = &SpriteBank::Instance().Fog;
}

Map::~Map() {
}

Terrain* Map::getTerrainAt(int pixelx, int pixely){
	int x = (pixelx + (terrainW) /2) / (terrainW);
	int y = (pixely + (terrainH) /2) / (terrainH);
	int index = (y * w) + x;
	if (index >= MAX_MAP_DIMENSION || index < 0)
		return nullptr;
	return &terrains[index];
}

Terrain* Map::getTerrainAtTerrains(int _x, int _y) {
	int index = (_y * w) + _x;
	if (index >= MAX_MAP_DIMENSION || index < 0)
		return nullptr;
	return &terrains[index];
}

Terrain* Map::getTerrainAtTerrains(Point &p) {
	int index = (p.y * w) + p.x;
	if (index >= MAX_MAP_DIMENSION || index < 0)
		return nullptr;
	return &terrains[index];
}

Point Map::getPositionInMap(int pixelx, int pixely) {
	int x = (pixelx + (terrainW) / 2) / (terrainW);
	int y = (pixely + (terrainH) / 2) / (terrainH);
	int index = (y * w) + x;
	if (index >= MAX_MAP_DIMENSION || index < 0) {
		return Point();
	}
	return Point(x, y);
}

Point Map::getPixelPositionInMap(int _x, int _y) {
	int index = (_y * w) + _x;
	if (index >= MAX_MAP_DIMENSION || index < 0)
		return Point();
	int x = terrains[index].getX();
	int y = terrains[index].getY();
	return Point(x, y);
}

void Map::generate() {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			Terrain terrain = Terrain();
			if ((x == 9 && y == 3) || (x == 9 && y == 4))
				terrain.setTile(Tile::wall);
			else
				terrain.setTile(Tile::grass);
			terrain.setPosition(x, y, terrainW, terrainH);
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
				collw = terrainW * xlen;
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
	if (t) {
		t->setTile(tile);
		generateCollisionMap();
	}
}

bool Map::isCollidingPredict(Sprite* sprite) {
	Rect rx = sprite->getPredictiveRectX();
	Rect ry = sprite->getPredictiveRectY();
	bool ret = false;
	for (int i = 0; i < collisionMap.size(); i++) {
		if (collisionMap[i].intersects(rx)) {
			sprite->revertXPos();
			ret = true;
		}
		if (collisionMap[i].intersects(ry)) {
			sprite->revertYPos();
			ret = true;
		}
	}
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
		if (collisionMap[i].collidedFromBot(r) || collisionMap[i].collidedFromTop(r)) {
			if (colType == CollisionType::VERTICAL)
				return CollisionType::CORNER;
			colType = CollisionType::HORIZONTAL;
		}
		if (collisionMap[i].collidedFromRight(r) || collisionMap[i].collidedFromLeft(r)) {
			if (colType == CollisionType::HORIZONTAL)
				return CollisionType::CORNER;
			colType = CollisionType::VERTICAL;
		}
	}
	return colType;
}

void Map::update() {
	for (int i = 0; i < w * h; i++) {
		terrains[i].setNonVisible();
	}
	shadowEngine.computeVisibleCells(chr->getMapPosition(), 15);
	render();
}

void Map::render() {
	for (int i = 0; i < w * h; i++) {
		int drawX = terrains[i].getDrawX();
		int drawY = terrains[i].getDrawY();
		switch (terrains[i].getTile()) {
		case Tile::grass:
			TextureManager::drawResized(*grass, drawX, drawY, terrainW, terrainH);
			break;
		case Tile::wall:
			TextureManager::drawResized(*wall, drawX, drawY, terrainW, terrainH);
			break;
		}
		if (!terrains[i].isVisible() && terrains[i].getTile() == Tile::grass) {
			TextureManager::drawResized(*fog, drawX, drawY, terrainW, terrainH);
		}
	}
	if (drawDebug) {
		for (int i = 0; i < collisionMap.size(); i++) {
			collisionMap[i].drawDebugBox();
		}
	}
}

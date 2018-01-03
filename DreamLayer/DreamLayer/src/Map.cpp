#include "Map.h"
#include "TextureManager.h"
#include "SpriteBank.h"
#include "Constants.h"


Map::Map() {
	w = 10;
	h = 10;
	terrainW = TILE_PIXELSIZE;
	terrainH = TILE_PIXELSIZE;
}

Map::~Map() {
}

Terrain* Map::getTerrainAt(int _x, int _y) {
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

void Map::handleTerrainCollision(Sprite* sprite) {
	int x = sprite->getRect().x;
	int y = sprite->getRect().y;
	int h = sprite->getRect().h;
	int w = sprite->getRect().w;
	//for (int i = 0; i < w * h; i++) {
	//	if (sprite->deltx != 0 && sprite->delty != 0) {
	//		if (terrains[i].getRect().intersects(Rect(x + SPEED, y + SPEED, w, h)) ||
	//			terrains[i].getRect().intersects(Rect(x - SPEED, y - SPEED, w, h)) ||
	//			terrains[i].getRect().intersects(Rect(x + SPEED, y - SPEED, w, h)) ||
	//			terrains[i].getRect().intersects(Rect(x - SPEED, y + SPEED, w, h))) {
	//			sprite->moveX = false;
	//			sprite->moveY = false;
	//			return;
	//		}
	//	}
	//	if (sprite->deltx != 0) {
	//		if (terrains[i].getRect().intersects(Rect(x + SPEED, y, w, h)) ||
	//			terrains[i].getRect().intersects(Rect(x - SPEED, y, w, h))) {
	//			sprite->moveX = false;
	//			return;
	//		}
	//	}
	//	if (sprite->delty != 0) {
	//		if (terrains[i].getRect().intersects(Rect(x, y + SPEED, w, h)) ||
	//			terrains[i].getRect().intersects(Rect(x, y - SPEED, w, h))) {
	//			sprite->moveY = false;
	//			return;
	//		}
	//	}
	//}
}

void Map::render() {
	for (int i = 0; i < w * h; i++) {
		terrains[i].render();
	}
	if (drawDebug) {
		for (std::vector<Rect>::iterator i = collisionMap.begin(); i != collisionMap.end(); i++) {
			i->drawDebugBox();
		}
	}
}

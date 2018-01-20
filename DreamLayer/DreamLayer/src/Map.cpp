#include "Map.h"
#include "TextureManager.h"
#include "SpriteBank.h"
#include "Constants.h"
#include "Game.h"
#include <stdlib.h>

Map::Map() {
	w = 500;
	h = 500;
	terrainW = TILE_RENDERSIZE;
	terrainH = TILE_RENDERSIZE;

	lightMapW = w * 4;
	lightMapH = h * 4;

	shadowEngine.setMap(*this);
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

Point Map::getPositionInLightMap(int pixelx, int pixely) {
	int x = (pixelx + (terrainW) / 2) / (terrainW);
	int y = (pixely + (terrainH) / 2) / (terrainH);

	if (x < 0)
		x = 0;
	else if (x >= getWidth())
		x = getWidth() - 1;
	if (y < 0)
		y = 0;
	else if (y >= getHeight())
		y = getHeight() - 1;

	int modx = (pixelx + (terrainW) / 2) % (terrainW);
	int mody = (pixely + (terrainH) / 2) % (terrainH);

	int lightx = modx / (terrainW / 4);
	int lighty = mody / (terrainH / 4);

	int retx = (x * 4) + lightx;
	int rety = (y * 4) + lighty;

	return Point(retx, rety);
}

Point Map::getPositionInMap(int pixelx, int pixely) {
	int x = (pixelx + (terrainW) / 2) / (terrainW);
	int y = (pixely + (terrainH) / 2) / (terrainH);
	if (x < 0)
		x = 0;
	else if (x >= getWidth())
		x = getWidth() - 1;
	if (y < 0)
		y = 0;
	else if (y >= getHeight())
		y = getHeight() - 1;
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
	int r;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			Terrain terrain = Terrain(terrainW, terrainH);
			r = rand() % 20;
			if (r <= 8)
				terrain.setTile(Tile::floor1);
			else if (r <= 16)
				terrain.setTile(Tile::floor2);
			else if (r <= 17)
				terrain.setTile(Tile::floorCrack);
			else if (r <= 18)
				terrain.setTile(Tile::floorDeco1);
			else
				terrain.setTile(Tile::floorDeco2);
			terrain.setPosition(x, y);
			terrains[(y * w) + x] = terrain;
		}
	}
	//generateCollisionMap();
}

void Map::clearMap() {
	int r;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			r = rand() % 20;
			if (r <= 6)
				terrains[(y * w) + x].setTile(Tile::floor1);
			else if (r <= 13)
				terrains[(y * w) + x].setTile(Tile::floor2);
			else if (r <= 15)
				terrains[(y * w) + x].setTile(Tile::floorCrack);
			else if (r <= 17)
				terrains[(y * w) + x].setTile(Tile::floorDeco1);
			else
				terrains[(y * w) + x].setTile(Tile::floorDeco2);
		}
	}
	//generateCollisionMap();
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
				collx = t.getTopLeftX();
				colly = t.getTopLeftY();
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

void Map::editTerrainAt(int pixelx, int pixely, int tile) {
	Terrain* t = getTerrainAt(pixelx, pixely);
	Point p = getPositionInMap(pixelx, pixely);
	if (t) {
		int index = 0;
		t->setTile(tile);
		if (t->obstacle) {
			for (int y = (p.y * 4); y < (p.y * 4) + 4; y++) {
				for (int x = (p.x * 4); x < (p.x * 4) + 4; x++) {
					index = (y * (lightMapW)) + x;
					lightMap.set(index);
				}
			}
		}
		else {
			for (int y = (p.y * 4); y < (p.y * 4) + 4; y++) {
				for (int x = (p.x * 4); x < (p.x * 4) + 4; x++) {
					index = (y * (lightMapW)) + x;
					lightMap.reset(index);
				}
			}
		}
		//generateCollisionMap();
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

void Map::getScannableTerrains() {
	int topX = (int)Game::camera.pos.x;
	int topY = (int)Game::camera.pos.y;
	int botX = (int)Game::camera.pos.x + (int)Game::camera.w;
	int botY = (int)Game::camera.pos.y + (int)Game::camera.h;

	checkStart = getPositionInMap(topX, topY);
	checkEnd = getPositionInMap(botX, botY);
}

void Map::update(float delta) {
	//Restrict operations to only local terrains
	getScannableTerrains();
	int localHeight = checkEnd.y - checkStart.y;
	int localWidth = checkEnd.x - checkStart.x;
	for (int y = (checkStart.y*4); y <= (checkStart.y * 4) + (localHeight*4) + 3; y++) {
		for (int x = (checkStart.x*4); x <= (checkStart.x * 4) + (localWidth*4) + 3; x++) {
			visibilityMap.reset((y * (lightMapW)) + x);
		}
	}
	//for (int y = (checkStart.y); y <= (checkStart.y) + (localHeight); y++) {
	//	for (int x = (checkStart.x); x <= (checkStart.x) + (localWidth); x++) {
	//		terrains[(y * w) + x].setNonVisible();
	//	}
	//}
	shadowEngine.computeVisibleCellsGradient(getPositionInLightMap(chr->pos.x, chr->pos.y), 40);
	//shadowEngine.computeVisibleCells(chr->getMapPosition(), 30);
	render(delta);
}

void Map::drawWall(int drawX, int drawY, int mapX, int mapY, Terrain &t, float delta) {
	//Draw vertical/horizontal walls depending on if there's a wall in front of it
	int index = ((mapY + 1) * w) + mapX;
	//BotNeighbor in this case is always true
	if (index < MAX_MAP_DIMENSION && terrains[index].obstacle) {
		bool topNeighbor = false;
		bool rightNeighbor = false;
		bool leftNeighbor = false;
		int checkTop = ((mapY - 1) * w) + mapX;
		if (mapY - 1 >= 0) {
			if (terrains[checkTop].obstacle) {
				topNeighbor = true;
			}
		}
		int checkRight = ((mapY)* w) + mapX + 1;
		if (mapX + 1 < getWidth()) {
			if (terrains[checkRight].obstacle) {
				rightNeighbor = true;
			}
		}
		int checkLeft = ((mapY)* w) + mapX - 1;
		if (mapX - 1 >= 0) {
			if (terrains[checkLeft].obstacle) {
				leftNeighbor = true;
			}
		}
		//  X
		// X[]X
		//  []
		if (!topNeighbor && !rightNeighbor && !leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallVertTopEnd, drawX, drawY, terrainW, terrainH);
		}
		//  []
		// X[]X
		//  []
		else if (topNeighbor && !rightNeighbor && !leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallVert, drawX, drawY, terrainW, (terrainH));
		}
		//  []
		// X[][]
		//  []
		else if (topNeighbor && rightNeighbor && !leftNeighbor) {
			//replace this with a different texture once the time comes
			TextureManager::drawResized(SpriteBank::Instance().WallVertRIntersect, drawX, drawY, terrainW, (terrainH));
		}
		//  []
		//[][][]
		//  []
		else if (topNeighbor && rightNeighbor && leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallVertIntersect, drawX, drawY, terrainW, (terrainH));
		}
		//  X
		// X[][]
		//  []
		else if (!topNeighbor && rightNeighbor && !leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallVertCorner, drawX, drawY, terrainW, (terrainH));
		}
		//  X
		//[][][]
		//  []
		else if (!topNeighbor && rightNeighbor && leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallVertTIntersect, drawX, drawY, terrainW, (terrainH));
		}
		//  X
		//[][]X
		//  []
		else if (!topNeighbor && !rightNeighbor && leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallVertCorner, drawX, drawY, terrainW, (terrainH), SDL_FLIP_HORIZONTAL);
		}
		//  []
		//[][]X
		//  []
		else if (topNeighbor && !rightNeighbor && leftNeighbor) {
			//replace this with a different texture once the time comes
			TextureManager::drawResized(SpriteBank::Instance().WallVertRIntersect, drawX, drawY, terrainW, (terrainH), SDL_FLIP_HORIZONTAL);
		}
	}
	else {
		bool topNeighbor = false;
		bool rightNeighbor = false;
		bool leftNeighbor = false;
		switch (t.getTile()) {
		case Tile::wall1:
			TextureManager::drawResized(SpriteBank::Instance().WallDark, drawX, drawY, terrainW, (terrainH * 2));
			break;
		case Tile::wall2:
			TextureManager::drawResized(SpriteBank::Instance().WallLight, drawX, drawY, terrainW, (terrainH * 2));
			break;
		case Tile::wallwater:
			t.updateAnimationIndex(delta);
			switch (t.getAnimationIndex()) {
			case 0:
				TextureManager::drawResized(SpriteBank::Instance().WallMoss1, drawX, drawY, terrainW, (terrainH * 2));
				break;
			case 1:
				TextureManager::drawResized(SpriteBank::Instance().WallMoss2, drawX, drawY, terrainW, (terrainH * 2));
				break;
			case 2:
				TextureManager::drawResized(SpriteBank::Instance().WallMoss3, drawX, drawY, terrainW, (terrainH * 2));
				break;
			default:
				TextureManager::drawResized(SpriteBank::Instance().WallMoss4, drawX, drawY, terrainW, (terrainH * 2));
				break;
			}
			break;
		default:
			break;
		}
		int checkTop = ((mapY - 1) * w) + mapX;
		if (mapY - 1 >= 0) {
			if (terrains[checkTop].obstacle) {
				topNeighbor = true;
			}
		}
		int checkRight = ((mapY) * w) + mapX + 1;
		if (mapX + 1 < getWidth()) {
			if (terrains[checkRight].obstacle) {
				rightNeighbor = true;
			}
		}
		int checkLeft = ((mapY)* w) + mapX - 1;
		if (mapX - 1 >= 0) {
			if (terrains[checkLeft].obstacle) {
				leftNeighbor = true;
			}
		}
		// 
		//  []
		if (!topNeighbor && !rightNeighbor && !leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallHorizIsolate, drawX, drawY, terrainW, (terrainH/2));
		}
		//  []
		// X[]X
		else if (topNeighbor && !rightNeighbor && !leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallHorizBotEnd, drawX, drawY, terrainW, (terrainH / 2));
		}
		//  [] 
		// X[][]
		else if (topNeighbor && rightNeighbor && !leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallHorizCorner, drawX, drawY, terrainW, (terrainH / 2));
		}
		//  []
		//[][][]
		else if (topNeighbor && rightNeighbor && leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallHorizOpenTop, drawX, drawY, terrainW, (terrainH / 2));
		}
		// 
		// X[][]
		else if (!topNeighbor && rightNeighbor && !leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallHorizEnd, drawX, drawY, terrainW, (terrainH / 2));
		}
		// 
		//[][][]
		else if (!topNeighbor && rightNeighbor && leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallHoriz, drawX, drawY, terrainW, (terrainH / 2));
		}
		// 
		//[][]X
		else if (!topNeighbor && !rightNeighbor && leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallHorizEnd, drawX, drawY, terrainW, (terrainH / 2), SDL_FLIP_HORIZONTAL);
		}
		//  []
		//[][]X
		else if (topNeighbor && !rightNeighbor && leftNeighbor) {
			TextureManager::drawResized(SpriteBank::Instance().WallHorizCorner, drawX, drawY, terrainW, (terrainH / 2), SDL_FLIP_HORIZONTAL);
		}
	}
}

void Map::render(float delta) {
	int localHeight = checkEnd.y - checkStart.y;
	int localWidth = checkEnd.x - checkStart.x;
	for (int y = checkStart.y; y <= checkStart.y + localHeight; y++) {
		for (int x = checkStart.x; x <= checkStart.x + localWidth; x++) {
			int drawX = terrains[(y * w) + x].getDrawX();
			int drawY = terrains[(y * w) + x].getDrawY();
			int topLeftY = terrains[(y * w) + x].getTopLeftY();
			switch (terrains[(y * w) + x].getTile()) {
			case Tile::floor1:
				TextureManager::drawResized(SpriteBank::Instance().Floor1, drawX, drawY, terrainW, terrainH);
				break;
			case Tile::floor2:
				TextureManager::drawResized(SpriteBank::Instance().Floor2, drawX, drawY, terrainW, terrainH);
				break;
			case Tile::floorCrack:
				TextureManager::drawResized(SpriteBank::Instance().FloorCrack, drawX, drawY, terrainW, terrainH);
				break;
			case Tile::floorDeco1:
				TextureManager::drawResized(SpriteBank::Instance().FloorDeco1, drawX, drawY, terrainW, terrainH);
				break;
			case Tile::floorDeco2:
				TextureManager::drawResized(SpriteBank::Instance().FloorDeco2, drawX, drawY, terrainW, terrainH);
				break;
			default:
				break;
			}
		}
	}
	if (drawDebug) {
		for (int i = 0; i < collisionMap.size(); i++) {
			collisionMap[i].drawDebugBox();
		}
	}
}

void Map::renderWallAndFogLayer(float delta) {
	int localHeight = checkEnd.y - checkStart.y;
	if (localHeight + 1 < getHeight())
		localHeight = localHeight + 1;
	int localWidth = checkEnd.x - checkStart.x;
	int fogW = terrainW / 4;
	int fogH = terrainH / 4;
	for (int y = (checkStart.y * 4); y <= (checkStart.y * 4) + (localHeight * 4) + 3; y++) {
		for (int x = (checkStart.x * 4); x <= (checkStart.x * 4) + (localWidth * 4) + 3; x++) {
			if (!lightMap[(y * lightMapW) + x] && !visibilityMap[(y * lightMapW) + x]) {
				TextureManager::drawResized(SpriteBank::Instance().Fog, (x * fogW) - (terrainW / 2), (y * fogH) - (terrainH / 2), fogW, fogH);
			}
		}
	}

	/*for (int y = (checkStart.y); y <= (checkStart.y) + (localHeight); y++) {
		for (int x = (checkStart.x); x <= (checkStart.x) + (localWidth); x++) {
			int drawX = terrains[(y * w) + x].getDrawX();
			int drawY = terrains[(y * w) + x].getDrawY();
			if(!terrains[(y * w) + x].isVisible() && !terrains[(y * w) + x].obstacle)
				TextureManager::drawResized(SpriteBank::Instance().Fog, drawX, drawY, terrainW, terrainH);
		}
	}*/

	//TODO: Optimize the wall drawing subroutine to reduce runtime.
	for (int y = checkStart.y; y <= checkStart.y + localHeight; y++) {
		for (int x = checkStart.x; x <= checkStart.x + localWidth; x++) {
			int drawX = terrains[(y * w) + x].getDrawX();
			int drawY = terrains[(y * w) + x].getDrawY();
			if (terrains[(y * w) + x].obstacle) {
				drawWall(drawX, drawY, x, y, terrains[(y * w) + x], delta);
			}
		}
	}
}

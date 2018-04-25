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
	pathFinder.setMap(*this);
}

Map::~Map() {
}

void Map::save(BinSerializer* b) {

}

void Map::load(BinReader* b) {

}

bool Map::getPath(Point start, Point end, Sprite &sprite, std::stack<Point>& pathOutput) {
	return pathFinder.findPath(start, end, pathOutput, sprite);
}

bool Map::isWithinTileVicinity(Point pixelpos, Point mapDestPos) {
	int x = terrains[(mapDestPos.y * w) + mapDestPos.x].getPixelPosX();
	int y = terrains[(mapDestPos.y * w) + mapDestPos.x].getPixelPosY();
	//10 pixels of breathing space should be enough
	return !(pixelpos.x > x + 10 || pixelpos.x < x - 10 ||
		pixelpos.y > y + 10 || pixelpos.y < y - 10);
}

void Map::resetPaths() {
	int index = 0;
	for (int y = 0; y < getHeight(); y++) {
		for (int x = 0; x < getWidth(); x++) {
			getTerrainAtTerrains(Point(x, y))->testPath = false;
		}
	}
}

bool Map::tileIsObstacle(int pixelx, int pixely) {
	int x = (pixelx + (terrainW) / 2) / (terrainW);
	int y = (pixely + (terrainH) / 2) / (terrainH);
	int index = (y * w) + x;
	if (index >= MAX_MAP_DIMENSION || index < 0)
		return true;
	return terrains[index].obstacle;
}

bool Map::tileIsObstacle(Point pixel) {
	return tileIsObstacle(pixel.x, pixel.y);
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
	return getTerrainAtTerrains(p.x, p.y);
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
	int x = terrains[index].getPixelPosX();
	int y = terrains[index].getPixelPosY();
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
	for (int i = 0; i < lightMap.size(); i++) {
		lightMap.reset(i);
	}
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
	}
}

bool Map::isTileTraversableAI(Point start, Point end, Sprite &sprite) {
	bool ret = false;
	if (end.x < 0 || end.x >= getWidth() || end.y < 0 || end.y >= getHeight()) {
		return false;
	}
	int x1 = terrains[(start.y * w) + start.x].getPixelPosX();
	int y1 = terrains[(start.y * w) + start.x].getPixelPosY();
	int x2 = terrains[(end.y * w) + end.x].getPixelPosX();
	int y2 = terrains[(end.y * w) + end.x].getPixelPosY();
	x1 = (x1 + x2)/2;
	y1 = (y1 + y2)/2;
	sprite.setPosition(x1, y1);
	ret = isColliding(sprite.getRect());
	return !ret;
}

//Check all 4 corners of the collision box for collision
bool Map::isColliding(Rect collBox) {
	return (tileIsObstacle(collBox.topLeft()) ||
		tileIsObstacle(collBox.topRight()) ||
		tileIsObstacle(collBox.botLeft()) ||
		tileIsObstacle(collBox.botRight()));
}

bool Map::willCollideHandle(Sprite* sprite) {
	Rect rx = sprite->getPredictiveRectX();
	Rect ry = sprite->getPredictiveRectY();
	bool ret = false;
	if (isColliding(rx)) {
		sprite->revertXPos();
		ret = true;
	}
	if (isColliding(ry)) {
		sprite->revertYPos();
		ret = true;
	}
	return ret;
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
	shadowEngine.computeVisibleCellsGradient(getPositionInLightMap(chr->pos.x, chr->pos.y), 40);
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
}

void Map::renderWallLayer(float delta) {
	int localHeight = checkEnd.y - checkStart.y;
	if (localHeight + 1 < getHeight())
		localHeight = localHeight + 1;
	int localWidth = checkEnd.x - checkStart.x;

	//TODO: Optimize the wall drawing subroutine to reduce runtime.
	for (int y = checkStart.y; y <= checkStart.y + localHeight; y++) {
		for (int x = checkStart.x; x <= checkStart.x + localWidth; x++) {
			int drawX = terrains[(y * w) + x].getDrawX();
			int drawY = terrains[(y * w) + x].getDrawY();
			if (terrains[(y * w) + x].obstacle) {
				drawWall(drawX, drawY, x, y, terrains[(y * w) + x], delta);
			}
			if (chr != nullptr && chr->getMapPosition().y == y) {
				chr->render();
			}
			if (mst != nullptr && mst->getMapPosition().y == y) {
				mst->render();
			}
		}
	}
	for (int y = checkStart.y; y <= checkStart.y + localHeight; y++) {
		for (int x = checkStart.x; x <= checkStart.x + localWidth; x++) {
			int drawX = terrains[(y * w) + x].getTopLeftX();
			int drawY = terrains[(y * w) + x].getTopLeftY();
			if (terrains[(y * w) + x].testPath)
				TextureManager::drawResized(SpriteBank::Instance().PathSegment, drawX, drawY, terrainW, terrainH);
		}
	}
}

void Map::renderFogLayer() {
	int localHeight = checkEnd.y - checkStart.y;
	if (localHeight + 1 < getHeight())
		localHeight = localHeight + 1;
	int localWidth = checkEnd.x - checkStart.x;
	short fogW = terrainW / 2;
	short fogH = terrainH / 2;
	short actualFogW = fogW / 2;
	short actualFogH = fogH / 2;
	bool hasWallTexture1 = false;
	bool hasWallTexture2 = false;
	//We want to ignore fog drawing in areas occupied by a wall texture
	for (int y = (checkStart.y * 4); y <= (checkStart.y * 4) + (localHeight * 4) + 3; y++) {
		for (int x = (checkStart.x * 4); x <= (checkStart.x * 4) + (localWidth * 4) + 3; x++) {
			if (((y + 2) * lightMapW) + x < MAX_MAP_DIMENSION * 16) {
				hasWallTexture1 = lightMap[((y + 2) * lightMapW) + x];
			}
			if (((y + 4) * lightMapW) + x < MAX_MAP_DIMENSION * 16) {
				hasWallTexture2 = lightMap[((y + 4) * lightMapW) + x];
			}
			if (!lightMap[(y * lightMapW) + x] && !visibilityMap[(y * lightMapW) + x]) {
				if (!hasWallTexture1 && !hasWallTexture2)
					TextureManager::drawResized(SpriteBank::Instance().Fog, ((x * actualFogW) - (terrainW / 2)) - (fogW / 4), ((y * actualFogH) - (terrainH / 2)) - (fogH / 4), fogW, fogH);
			}
			hasWallTexture1 = false;
			hasWallTexture2 = false;
		}
	}
}

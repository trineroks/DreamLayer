#include "Terrain.h"
#include "SpriteBank.h"

Terrain::Terrain() {
}


Terrain::~Terrain() {
}

Terrain::Terrain(short _w, short _h) {
	w = _w;
	h = _h;
}

void Terrain::setPosition(int _x, int _y) {
	x = _x * w;
	y = _y * h;
	drawX = x - ((int)w / 2);
	drawY = y - ((int)h / 2);
}

void Terrain::setTile(unsigned char _tile) {
	tile = _tile;
	switch (tile) {
	case Tile::grass:
		texRegion = &SpriteBank::Instance().Grass;
		break;
	case Tile::wall:
		texRegion = &SpriteBank::Instance().Wall;
		obstacle = true;
		break;
	default:
		break;
	}
}

void Terrain::render() {
	if (texRegion) {
		TextureManager::drawResized(*texRegion, drawX, drawY, w, h);
	}
}
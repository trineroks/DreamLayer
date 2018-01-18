#include "Terrain.h"
#include "SpriteBank.h"
#include "Constants.h"

Terrain::Terrain() {
}


Terrain::~Terrain() {
}

void Terrain::setPosition(int _x, int _y, int _w, int _h) {
	x = _x * _w;
	y = _y * _h;
	drawX = x - (int)(_w / 2);
	drawY = y - (int)(_h / 2);
}

void Terrain::setTile(unsigned char _tile) {
	tile = _tile;
	switch (tile) {
	case Tile::wall:
		obstacle = true;
		break;
	default:
		obstacle = false;
		break;
	}
}
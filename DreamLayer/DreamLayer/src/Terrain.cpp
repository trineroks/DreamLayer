#include "Terrain.h"
#include "SpriteBank.h"
#include "Constants.h"

Terrain::Terrain(short _w, short _h) {
	w = _w;
	h = _h;
}


Terrain::~Terrain() {
}

void Terrain::setPosition(int _x, int _y) {
	x = _x * w;
	y = _y * h;
	modifyDrawCoords();
}

void Terrain::modifyDrawCoords() {
	drawX = x - (int)(w / 2);
	topLeftX = drawX;
	if (obstacle) {
		int wallH = h * 2;
		drawY = y - (int)(wallH - (h / 2));
		topLeftY = drawY + h;
	}
	else {
		drawY = y - (int)(h / 2);
		topLeftY = drawY;
	}
}

void Terrain::setTile(unsigned char _tile) {
	tile = _tile;
	switch (tile) {
	case Tile::wall1:
		obstacle = true;
		break;
	case Tile::wall2:
		obstacle = true;
		break;
	case Tile::wall3:
		obstacle = true;
		break;
	case Tile::wallwater:
		obstacle = true;
		maxAnimationIndex = 3;
		break;
	default:
		obstacle = false;
		break;
	}
	modifyDrawCoords();
}
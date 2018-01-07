#pragma once
#include "Rect.h"
#include "Tile.h"
#include "TextureRegion.h"

class Terrain {
public:
	Terrain();
	Terrain(short _w, short _h);
	~Terrain();

	//Position is always oriented center for terrains, 
	//Parameters - the 2D array position. Will be converted
	//to pixel position within the function.
	void setPosition(int _x, int _y);

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	int getDrawX() {
		return drawX;
	}

	int getDrawY() {
		return drawY;
	}

	void setTile(unsigned char _tile);

	const unsigned char getTile() const {
		return tile;
	}
	
	void render();
	
	bool obstacle = false;
private:
	int x = 0;
	int y = 0;

	unsigned char tile = Tile::nil;

	int drawX = 0;
	int drawY = 0;

	short w = 0;
	short h = 0;

	TextureRegion* texRegion = nullptr;
};


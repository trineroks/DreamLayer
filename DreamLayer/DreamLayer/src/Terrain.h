#pragma once
#include "Rect.h"
#include "Tile.h"

class Terrain {
public:
	Terrain();
	~Terrain();

	//Position is always oriented center for terrains, 
	//Parameters - the 2D array position. Will be converted
	//to pixel position within the function.
	void setPosition(int _x, int _y, int _w, int _h);

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
	
	bool isVisible() {
		return visible;
	}

	void setVisible() {
		visible = true;
	}

	void setNonVisible() {
		visible = false;
	}
	
	bool obstacle = false;
private:
	int x = 0;
	int y = 0;

	unsigned char tile = Tile::nil;
	bool visible = false;

	int drawX = 0;
	int drawY = 0;
};


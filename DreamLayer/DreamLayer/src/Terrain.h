#pragma once
#include "Rect.h"
#include "Tile.h"
#include "Serializable.h"

class Terrain : public Serializable {
public:
	Terrain(short _w, short _h);
	Terrain() {}
	~Terrain();

	//Position is always oriented center for terrains, 
	//Parameters - the 2D array position. Will be converted
	//to pixel position within the function.
	void setPosition(int _x, int _y);

	void save(BinSerializer* b) override;
	void load(BinReader* b) override;

	//Position in pixels, oriented at center
	int getPixelPosX() {
		return x;
	}

	//Position in pixels, oriented at center
	int getPixelPosY() {
		return y;
	}

	int getTopLeftX() {
		return topLeftX;
	}

	int getTopLeftY() {
		return topLeftY;
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

	short getAnimationIndex() {
		return animationIndex;
	}

	void updateAnimationIndex(float delta) {
		currTime += delta;
		if (currTime >= speed) {
			animationIndex++;
			currTime = 0.0f;
			if (animationIndex > maxAnimationIndex)
				animationIndex = 0;
		}
	}

	void resetAnimationIndex() {
		animationIndex = 0;
	}

	bool obstacle = false;
	bool wall = false;

	bool testPath = false;
private:

	void modifyDrawCoords();
	int x = 0;
	int y = 0;

	short w = 0;
	short h = 0;

	unsigned char tile = Tile::nil;

	int drawX = 0;
	int drawY = 0;

	int topLeftX = 0;
	int topLeftY = 0;

	float currTime = 0.0f;
	float speed = 100.0f;
	short animationIndex = 0;
	short maxAnimationIndex = 0;
};


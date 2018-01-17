#pragma once
#include "Sprite.h"
#include "Map.h"
#include "Constants.h"

class Map;
class Character : public Sprite {
public:
	Character(TextureRegion &primaryRegion, TextureRegion &holsterRegion);
	Character();
	~Character();

	void updateHolstered(Map *map);
	void update(Map *map);

	bool getHolstered() {
		return holstered;
	}

	Point getMapPosition() {
		return mapPosition;
	}

private:
	Point mapPosition;
	bool holstered = false;
	TextureRegion *holster;
	TextureRegion *primary;
	Rect holsterBox;
	int armLength = 0;
};


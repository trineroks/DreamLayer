#pragma once
#include "Sprite.h"
#include "Map.h"

class Character : public Sprite {
public:
	Character(TextureRegion &primaryRegion, TextureRegion &holsterRegion);
	Character();
	~Character();

	void updateHolstered(Map *map);
	void update(Map *map);
private:
	TextureRegion *holster;
	TextureRegion *primary;
	Rect holsterBox;
	int armLength = 0;
};


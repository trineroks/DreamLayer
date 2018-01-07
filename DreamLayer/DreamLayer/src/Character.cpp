#include "Character.h"
#include "Tile.h"

Character::Character(TextureRegion &primaryRegion, TextureRegion &holsterRegion)
	: Sprite(primaryRegion)
{
	holster = &holsterRegion;
	primary = &primaryRegion;
}

Character::Character() {
}


Character::~Character() {
}

void Character::update(Map* map) {
	Sprite::update();
	updateHolstered(map);
}

void Character::updateHolstered(Map* map) {
	int h = primary->getRect().h * hscale;
	float radian = (angle + 90.0f) * (PI / 180.0f);
	//45 - yoffset is where the start of the pistol is, do pixel collision checking to see if this collides with a wall 
	//and if so holster the weapon.
	for (int i = (45 * hscale) - yoffset; i < h - yoffset; i++) { 
		int x1 = pos.x + (i * cos(radian));
		int y1 = pos.y + (i * sin(radian));
		if (map->getTerrainAt((int)x1, (int)y1)->obstacle) {
			setTextureRegion(*holster);
			holstered = true;
			return;
		}
	}
	holstered = false;
	setTextureRegion(*primary);
}

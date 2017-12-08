#include "Sprite.h"

Sprite::Sprite(TextureRegion *texRegion) {
	region = texRegion;
}

void Sprite::update() {
	x += deltx;
	y += delty;
	TextureManager::drawResized(region, x, y, 80, 80);
}

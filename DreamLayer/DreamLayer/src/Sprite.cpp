#include "Sprite.h"

Sprite::Sprite(TextureRegion *texRegion) {
	region = texRegion;
	setCollisionBox(new Rect(region->getRect().x, region->getRect().y, 
					region->getRect().w, region->getRect().h));
}

Sprite::~Sprite() {
	delete rect;
}

void Sprite::setPosition(int _x, int _y) {
	x = _x;
	y = _y;
}

void Sprite::setCollisionBox(Rect* box) {
	rect = box;
}

void Sprite::update() {
	x += deltx;
	y += delty;
	rect->setPos(x, y);
	TextureManager::drawResized(region, x, y, 80, 80);
}

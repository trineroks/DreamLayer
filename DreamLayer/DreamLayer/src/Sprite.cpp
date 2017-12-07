#include "Sprite.h"

Sprite::Sprite(const char* path) {
	setTexture(path);
}

void Sprite::setTexture(const char* path) {
	texture = TextureManager::loadTexture(path);

	src.x = src.y = 0;
	src.w = 678;
	src.h = 673;

	dest.w = dest.h = 128;
}

void Sprite::update() {
	dest.x = x;
	dest.y = y;
	TextureManager::draw(texture, src, dest);
}

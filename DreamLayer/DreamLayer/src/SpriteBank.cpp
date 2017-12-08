#include "SpriteBank.h"

SpriteBank::SpriteBank() {
}

SpriteBank::~SpriteBank() {
}

SpriteBank &SpriteBank::Instance() {
	static SpriteBank instance;
	return instance;
}

void SpriteBank::reload() {
	clear();
	load();
}

void SpriteBank::load() {
	SDL_Texture* sprite = TextureManager::loadTexture("assets/GhostAvi.png");

	Player = new TextureRegion(sprite, 0, 0, 678, 673);
}

void SpriteBank::clear() {
	delete Player;
	Player = nullptr;
}

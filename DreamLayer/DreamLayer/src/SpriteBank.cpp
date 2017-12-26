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
	SDL_Texture* box = TextureManager::loadTexture("assets/CollisionBox.png");
	SDL_Texture* spy = TextureManager::loadTexture("assets/spyRotatable.png");

	Player = new TextureRegion(sprite, 0, 0, 678, 673);
	TestCollisionBox = new TextureRegion(box, 0, 0, 64, 64);
	Spy = new TextureRegion(spy, 0, 0, 50, 68);
}

void SpriteBank::clear() {
	delete Player;
	delete TestCollisionBox;
	delete Spy;


	Player = nullptr;
	TestCollisionBox = nullptr;
	Spy = nullptr;
}

#include "SpriteBank.h"
#include "Constants.h"

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
	//find some way to eventually destroy these textures - combine them all into a spritesheet and make that a member of SpriteBank, destroy in clear()
	sprite = TextureManager::loadTexture("assets/GhostAvi.png");
	box = TextureManager::loadTexture("assets/CollisionBox.png");
	spy = TextureManager::loadTexture("assets/spyRotatable.png");
	crosshair = TextureManager::loadTexture("assets/crosshairs.png");
	bullet = TextureManager::loadTexture("assets/bullet.png");
	grass = TextureManager::loadTexture("assets/grass.png");
	wall = TextureManager::loadTexture("assets/wall.png");
	spyHolstered = TextureManager::loadTexture("assets/spyRotatableHolstered.png");

	Player = TextureRegion(sprite, 0, 0, 678, 673);
	TestCollisionBox = TextureRegion(box, 0, 0, 64, 64);
	Spy = TextureRegion(spy, 0, 0, 50, 68);
	SpyHolstered = TextureRegion(spyHolstered, 0, 0, 50, 45);
	Crosshair = TextureRegion(crosshair, 0, 0, 24, 24);
	Bullet = TextureRegion(bullet, 0, 0, 3, 8);
	Grass = TextureRegion(grass, 0, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	Wall = TextureRegion(wall, 0, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
}

void SpriteBank::clear() {
	SDL_DestroyTexture(sprite);
	SDL_DestroyTexture(box);
	SDL_DestroyTexture(spy);
	SDL_DestroyTexture(spyHolstered);
	SDL_DestroyTexture(crosshair);
	SDL_DestroyTexture(bullet);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(wall);
}

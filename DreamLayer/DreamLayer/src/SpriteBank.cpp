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
	terrains = TextureManager::loadTexture("assets/Terrains.png");
	wall1 = TextureManager::loadTexture("assets/Wall1.png");
	wall2 = TextureManager::loadTexture("assets/Wall2.png");
	wall3 = TextureManager::loadTexture("assets/Wall3.png");
	wallwater1 = TextureManager::loadTexture("assets/WallWater1.png");
	wallwater2 = TextureManager::loadTexture("assets/WallWater2.png");
	walltop = TextureManager::loadTexture("assets/WallTop.png");

	//find some way to eventually destroy these textures - combine them all into a spritesheet and make that a member of SpriteBank, destroy in clear()
	sprite = TextureManager::loadTexture("assets/GhostAvi.png");
	box = TextureManager::loadTexture("assets/CollisionBox.png");
	spy = TextureManager::loadTexture("assets/spyRotatable.png");
	crosshair = TextureManager::loadTexture("assets/crosshairs.png");
	bullet = TextureManager::loadTexture("assets/bullet.png");
	wall = TextureManager::loadTexture("assets/wall.png");
	spyHolstered = TextureManager::loadTexture("assets/spyRotatableHolstered.png");
	fog = TextureManager::loadTexture("assets/fog.png");
	

	Player = TextureRegion(sprite, 0, 0, 678, 673);
	TestCollisionBox = TextureRegion(box, 0, 0, 64, 64);
	Spy = TextureRegion(spy, 0, 0, 50, 68);
	SpyHolstered = TextureRegion(spyHolstered, 0, 0, 50, 45);
	Crosshair = TextureRegion(crosshair, 0, 0, 24, 24);
	Bullet = TextureRegion(bullet, 0, 0, 3, 8);

	Wall = TextureRegion(wall, 0, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	Fog = TextureRegion(fog, 0, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);

	Floor1 = TextureRegion(terrains, 0, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	Floor2 = TextureRegion(terrains, 64, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	FloorCrack = TextureRegion(terrains, 128, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	FloorDeco1 = TextureRegion(terrains, 192, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	FloorDeco2 = TextureRegion(terrains, 256, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	Wall1 = TextureRegion(wall1, 0, 0, TILE_PIXELSIZE, WALL_HEIGHT);
	Wall2 = TextureRegion(wall2, 0, 0, TILE_PIXELSIZE, WALL_HEIGHT);
	Wall3 = TextureRegion(wall3, 0, 0, TILE_PIXELSIZE, WALL_HEIGHT);
	WallWater1 = TextureRegion(wallwater1, 0, 0, TILE_PIXELSIZE, WALL_HEIGHT);
	WallWater2 = TextureRegion(wallwater2, 0, 0, TILE_PIXELSIZE, WALL_HEIGHT);
	WallTop = TextureRegion(walltop, 0, 0, TILE_PIXELSIZE, WALL_HEIGHT);
}

void SpriteBank::clear() {
	SDL_DestroyTexture(terrains);
	SDL_DestroyTexture(wall1);
	SDL_DestroyTexture(wall2);
	SDL_DestroyTexture(wall3);
	SDL_DestroyTexture(wallwater1);
	SDL_DestroyTexture(wallwater2);

	SDL_DestroyTexture(sprite);
	SDL_DestroyTexture(box);
	SDL_DestroyTexture(spy);
	SDL_DestroyTexture(spyHolstered);
	SDL_DestroyTexture(crosshair);
	SDL_DestroyTexture(bullet);
	SDL_DestroyTexture(wall);
	SDL_DestroyTexture(fog);
}

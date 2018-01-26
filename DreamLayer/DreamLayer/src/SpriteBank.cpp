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
	wall = TextureManager::loadTexture("assets/Wall.png");
	walltop = TextureManager::loadTexture("assets/WallTop.png");
	player = TextureManager::loadTexture("assets/PlaceHolder.png");

	//find some way to eventually destroy these textures - combine them all into a spritesheet and make that a member of SpriteBank, destroy in clear()
	box = TextureManager::loadTexture("assets/CollisionBox.png");
	crosshair = TextureManager::loadTexture("assets/crosshairs.png");
	bullet = TextureManager::loadTexture("assets/bullet.png");
	fog = TextureManager::loadTexture("assets/fogfade.png");
	

	TestCollisionBox = TextureRegion(box, 0, 0, 64, 64);
	Crosshair = TextureRegion(crosshair, 0, 0, 24, 24);
	Bullet = TextureRegion(bullet, 0, 0, 3, 8);

	Fog = TextureRegion(fog, 0, 0, 32, 32);

	Floor1 = TextureRegion(terrains, 0, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	Floor2 = TextureRegion(terrains, 64, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	FloorCrack = TextureRegion(terrains, 128, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	FloorDeco1 = TextureRegion(terrains, 192, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	FloorDeco2 = TextureRegion(terrains, 256, 0, TILE_PIXELSIZE, TILE_PIXELSIZE);
	WallDark = TextureRegion(wall, 0, 0, TILE_PIXELSIZE, WALL_HEIGHT);
	WallLight = TextureRegion(wall, 0, 128, TILE_PIXELSIZE, WALL_HEIGHT);
	WallMoss1 = TextureRegion(wall, 0, 256, TILE_PIXELSIZE, WALL_HEIGHT);
	WallMoss2 = TextureRegion(wall, 0, 384, TILE_PIXELSIZE, WALL_HEIGHT);
	WallMoss3 = TextureRegion(wall, 0, 512, TILE_PIXELSIZE, WALL_HEIGHT);
	WallMoss4 = TextureRegion(wall, 0, 640, TILE_PIXELSIZE, WALL_HEIGHT);

	PlayerE = TextureRegion(player, 0, 0, 64, 96);
	PlayerN = TextureRegion(player, 0, 96, 64, 96);
	PlayerNE = TextureRegion(player, 0, 192, 64, 96);
	PlayerS = TextureRegion(player, 0, 288, 64, 96);
	PlayerSE = TextureRegion(player, 0, 384, 64, 96);

	WallHoriz = TextureRegion(walltop, 0, 0, TILE_PIXELSIZE, 32);
	WallHorizBotEnd = TextureRegion(walltop, 0, 32, TILE_PIXELSIZE, 32);
	WallHorizCorner = TextureRegion(walltop, 0, 64, TILE_PIXELSIZE, 32);
	WallHorizEnd = TextureRegion(walltop, 0, 96, TILE_PIXELSIZE, 32);
	WallHorizIsolate = TextureRegion(walltop, 0, 128, TILE_PIXELSIZE, 32);
	WallHorizOpenTop = TextureRegion(walltop, 0, 160, TILE_PIXELSIZE, 32);
	WallVert = TextureRegion(walltop, 0, 192, TILE_PIXELSIZE, TILE_PIXELSIZE);
	WallVertCorner = TextureRegion(walltop, 0, 256, TILE_PIXELSIZE, TILE_PIXELSIZE);
	WallVertIntersect = TextureRegion(walltop, 0, 320, TILE_PIXELSIZE, TILE_PIXELSIZE);
	WallVertRIntersect = TextureRegion(walltop, 0, 384, TILE_PIXELSIZE, TILE_PIXELSIZE);
	WallVertTIntersect = TextureRegion(walltop, 0, 448, TILE_PIXELSIZE, TILE_PIXELSIZE);
	WallVertTopEnd = TextureRegion(walltop, 0, 512, TILE_PIXELSIZE, TILE_PIXELSIZE);
}

void SpriteBank::clear() {
	SDL_DestroyTexture(terrains);
	SDL_DestroyTexture(walltop);

	SDL_DestroyTexture(box);
	SDL_DestroyTexture(player);
	SDL_DestroyTexture(crosshair);
	SDL_DestroyTexture(bullet);
	SDL_DestroyTexture(wall);
	SDL_DestroyTexture(fog);
}

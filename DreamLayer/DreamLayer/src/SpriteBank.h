#pragma once
#include "SDL.h"
#include "TextureManager.h"

class TextureRegion;
class SpriteBank {
public:
	static SpriteBank &Instance();

	SpriteBank();
	~SpriteBank();

	void load();
	void reload();
	void clear();

	TextureRegion Player;
	TextureRegion TestCollisionBox;
	TextureRegion Spy;
	TextureRegion SpyHolstered;
	TextureRegion Crosshair;
	TextureRegion Bullet;

	TextureRegion Floor1;
	TextureRegion Floor2;
	TextureRegion FloorCrack;
	TextureRegion FloorDeco1;
	TextureRegion FloorDeco2;
	TextureRegion Wall1;
	TextureRegion Wall2;
	TextureRegion Wall3;
	TextureRegion WallWater1;
	TextureRegion WallWater2;
	TextureRegion WallTop;

	TextureRegion Wall;
	TextureRegion Fog;

private:
	SDL_Texture* sprite;
	SDL_Texture* box;
	SDL_Texture* spy;
	SDL_Texture* crosshair;
	SDL_Texture* bullet;

	SDL_Texture* terrains;
	SDL_Texture* wall1;
	SDL_Texture* wall2;
	SDL_Texture* wall3;
	SDL_Texture* wallwater2;
	SDL_Texture* wallwater1;
	SDL_Texture* walltop;

	SDL_Texture* wall;
	SDL_Texture* spyHolstered;
	SDL_Texture* fog;
};


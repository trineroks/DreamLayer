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

	TextureRegion Grass;
	TextureRegion Wall;

private:
	SDL_Texture* sprite;
	SDL_Texture* box;
	SDL_Texture* spy;
	SDL_Texture* crosshair;
	SDL_Texture* bullet;
	SDL_Texture* grass;
	SDL_Texture* wall;
	SDL_Texture* spyHolstered;
};


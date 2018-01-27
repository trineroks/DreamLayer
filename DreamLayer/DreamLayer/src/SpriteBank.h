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
	TextureRegion Crosshair;
	TextureRegion Bullet;

	TextureRegion Floor1;
	TextureRegion Floor2;
	TextureRegion FloorCrack;
	TextureRegion FloorDeco1;
	TextureRegion FloorDeco2;
	TextureRegion WallDark;
	TextureRegion WallLight;
	TextureRegion WallMoss1;
	TextureRegion WallMoss2;
	TextureRegion WallMoss3;
	TextureRegion WallMoss4;

	TextureRegion WallHoriz;
	TextureRegion WallHorizBotEnd;
	TextureRegion WallHorizCorner;
	TextureRegion WallHorizEnd;
	TextureRegion WallHorizIsolate;
	TextureRegion WallHorizOpenTop;
	TextureRegion WallVert;
	TextureRegion WallVertCorner;
	TextureRegion WallVertIntersect;
	TextureRegion WallVertTIntersect;
	TextureRegion WallVertTopEnd;
	TextureRegion WallVertRIntersect;

	TextureRegion PlayerN;
	TextureRegion PlayerS;
	TextureRegion PlayerNE;
	TextureRegion PlayerSE;
	TextureRegion PlayerE;

	TextureRegion Wall;
	TextureRegion Fog;

	TextureRegion PathSegment;

private:
	SDL_Texture* player;
	SDL_Texture* box;
	SDL_Texture* crosshair;
	SDL_Texture* bullet;

	SDL_Texture* terrains;
	SDL_Texture* wall;
	SDL_Texture* walltop;

	SDL_Texture* fog;
	SDL_Texture* pathsegment;
};


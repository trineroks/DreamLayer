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

	TextureRegion* Player;
	TextureRegion* TestCollisionBox;
	TextureRegion* Spy;
};


#pragma once
#include <vector>
#include "TextureRegion.h"
#include <cassert>

class Animation {
public:
	Animation();

	void addFrame(TextureRegion tex);

	TextureRegion& getFrame(int i);
	int getSize() const;

private:
	std::vector<TextureRegion> textures; //create copies for memory contiguousness
};


#include "TextureRegion.h"

TextureRegion::TextureRegion() {
}

TextureRegion::~TextureRegion() {
}

TextureRegion::TextureRegion(SDL_Texture* tex, int x, int y, int w, int h) {
	texture = tex;
	setRegion(x, y, w, h);
}

void TextureRegion::setRegion(int x, int y, int w, int h) {
	region.x = x;
	region.y = y;
	region.w = w;
	region.h = h;
}

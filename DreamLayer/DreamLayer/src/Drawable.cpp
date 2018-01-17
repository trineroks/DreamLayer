#include "Drawable.h"



Drawable::Drawable() {
}

Drawable::Drawable(TextureRegion &texRegion) {
	region = &texRegion;
	wdraw = region->getRect().w;
	hdraw = region->getRect().h;
}

Drawable::~Drawable() {
}

void Drawable::render() {
	if (region) {
		TextureManager::drawResized(*region, xdraw, ydraw, (wdraw * wscale), (hdraw * hscale), angle, (xoffset * wscale), (yoffset * hscale), flip);
	}
}

void Drawable::renderStatic() {
	if (region) {
		TextureManager::drawResizedStatic(*region, xdraw, ydraw, (wdraw * wscale), (hdraw * hscale), angle, (xoffset * wscale), (yoffset * hscale), flip);
	}
}

#include "Sprite.h"

Sprite::Sprite(TextureRegion *texRegion) {
	region = texRegion;
	setCollisionBox(Rect(0, 0, region->getRect().w, region->getRect().h));
	wdraw = region->getRect().w;
	hdraw = region->getRect().h;
}

Sprite::~Sprite() {
}

void Sprite::setPosition(int _x, int _y) {
	x = _x;
	y = _y;
}

void Sprite::setCollisionBox(Rect box) {
	rect = box;
}

void Sprite::scaleSprite(int w, int h) {
	wdraw = w;
	hdraw = h;
}

void Sprite::scaleSpriteAndCollisionBox(int w, int h) {
	wdraw = w;
	hdraw = h;
	setCollisionBox(Rect(0, 0, wdraw, hdraw));
}

void Sprite::update() {
	int xrect = x; 
	int yrect = y;
	switch (posType) {
	case TOPLEFT: 
		rect.setPos(xrect, yrect);
		xdraw = (int)x;
		ydraw = (int)y;
		break;
	case CENTER:
		xrect = (int)x - (rect.w / 2);
		yrect = (int)y - (rect.h / 2);
		xdraw = (int)x - (wdraw / 2);
		ydraw = (int)y - (hdraw / 2);
		rect.setPos(xrect, yrect);
		break;
	case BOTTOMCENTER:
		xrect = (int)x - (rect.w / 2);
		yrect = (int)y - rect.h;
		xdraw = (int)x - (wdraw / 2);
		ydraw = (int)y - hdraw;
		rect.setPos(xrect, yrect);
		break;
	case CUSTOM:
		xrect = (int)x - xoffset + collxOffset;
		yrect = (int)y - yoffset + collyOffset;
		xdraw = (int)x - xoffset;
		ydraw = (int)y - yoffset;
		rect.setPos(xrect, yrect);
		break;
	default:
		rect.setPos(xrect, yrect);
		xdraw = (int)x;
		ydraw = (int)y;
		break;
	}
	x += deltx * SPEED;
	y += delty * SPEED;
}

void Sprite::render() {
	TextureManager::drawResized(region, xdraw, ydraw, wdraw, hdraw, angle, 25, 16);
	if (drawDebug)
		rect.drawDebugBox();
}

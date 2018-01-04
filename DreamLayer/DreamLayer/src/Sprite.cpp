#include "Sprite.h"
#include <stdio.h>

Sprite::Sprite(TextureRegion &texRegion) {
	region = &texRegion;
	setCollisionBox(Rect(0, 0, region->getRect().w, region->getRect().h));
	wdraw = region->getRect().w;
	hdraw = region->getRect().h;
}

Sprite::Sprite() {

}

Sprite::~Sprite() {
}

void Sprite::setPosition(int _x, int _y) {
	prevPos.x = pos.x;
	prevPos.y = pos.y;

	pos.x = _x;
	pos.y = _y;
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
	prevPos.x = pos.x;
	prevPos.y = pos.y;
	pos.x += delta.x * SPEED;
	pos.y += delta.y * SPEED;

	int xrect = pos.x;
	int yrect = pos.y;
	switch (posType) {
	case TOPLEFT:
		xdraw = (int)pos.x;
		ydraw = (int)pos.y;
		rect.setPos(xrect, yrect);
		break;
	case CENTER:
		xrect = (int)pos.x - (rect.w / 2);
		yrect = (int)pos.y - (rect.h / 2);
		xdraw = (int)pos.x - (wdraw / 2);
		ydraw = (int)pos.y - (hdraw / 2);
		rect.setPos(xrect, yrect);
		break;
	case BOTTOMCENTER:
		xrect = (int)pos.x - (rect.w / 2);
		yrect = (int)pos.y - rect.h;
		xdraw = (int)pos.x - (wdraw / 2);
		ydraw = (int)pos.y - hdraw;
		rect.setPos(xrect, yrect);
		break;
	case CUSTOM:
		xrect = (int)pos.x - xoffset + collxOffset;
		yrect = (int)pos.y - yoffset + collyOffset;
		xdraw = (int)pos.x - xoffset;
		ydraw = (int)pos.y - yoffset;
		rect.setPos(xrect, yrect);
		break;
	default:
		rect.setPos(xrect, yrect);
		xdraw = (int)pos.x;
		ydraw = (int)pos.y;
		break;
	}
}

Rect Sprite::getPredictiveX() {
	Rect p = rect;
	p.x = rect.x +(delta.x * SPEED);//(deltx * SPEED);
	return p;
}

Rect Sprite::getPredictiveY() {
	Rect p = rect;
	p.y = rect.y +(delta.y * SPEED);//(delty * SPEED);
	return p;
}

void Sprite::render() {
	TextureManager::drawResized(*region, xdraw, ydraw, wdraw, hdraw, angle, xoffset, yoffset);
	if (drawDebug)
		rect.drawDebugBox();
}

#include "Sprite.h"
#include <stdio.h>

Sprite::Sprite(TextureRegion &texRegion) : Drawable(texRegion) {
	setCollisionBox(Rect(0, 0, region->getRect().w, region->getRect().h));
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

	xdraw = (int)pos.x - xoffset;
	ydraw = (int)pos.y - yoffset;
	rect.setPos((int)pos.x - collxOffset, (int)pos.y - collyOffset);
}

void Sprite::setCollisionBox(Rect box) {
	rect = box;
}

void Sprite::setTextureRegion(TextureRegion &tex) {
	region = &tex;
	wdraw = region->getRect().w;
	hdraw = region->getRect().h;
}

void Sprite::scale(float w, float h) {
	wscale = w;
	hscale = h;

	rect.wscale = wscale;
	rect.hscale = hscale;
}


void Sprite::setCustomOrientationType(int _xoffset, int _yoffset, int _collxOffset, int _collyOffset) {
	xoffset = _xoffset;
	yoffset = _yoffset;
	collxOffset = _xoffset - _collxOffset;
	collyOffset = _yoffset - _collyOffset;
}

void Sprite::setOrientationType(PositionType type) {
	switch (type) {
	case TOPLEFT:
		xoffset = 0;
		yoffset = 0;
		collxOffset = 0;
		collyOffset = 0;
		break;
	case CENTER:
		xoffset = wdraw / 2;
		yoffset = hdraw / 2;
		collxOffset = rect.w / 2;
		collyOffset = rect.h / 2;
		break;
	case BOTTOMCENTER:
		xoffset = wdraw / 2;
		yoffset = hdraw;
		collxOffset = rect.w / 2;
		collyOffset = rect.h;
		break;
	default:
		xoffset = 0;
		yoffset = 0;
		collxOffset = 0;
		collyOffset = 0;
		break;
	}
}

void Sprite::update() {
	prevPos.x = pos.x;
	prevPos.y = pos.y;
	pos.x += delta.x * SPEED;
	pos.y += delta.y * SPEED;

	xdraw = (int)pos.x - (xoffset * wscale);
	ydraw = (int)pos.y - (yoffset * hscale);
	rect.setPos((int)pos.x - (collxOffset * rect.wscale), (int)pos.y - (collyOffset * rect.hscale));
}

Rect Sprite::getPredictiveRectX() {
	Rect p = rect;
	p.x = rect.x +(delta.x * SPEED);
	return p;
}

Rect Sprite::getPredictiveRectY() {
	Rect p = rect;
	p.y = rect.y +(delta.y * SPEED);
	return p;
}

Rect Sprite::getPredictiveRect() {
	Rect p = rect;
	p.x = rect.x + (delta.x * SPEED);
	p.y = rect.y + (delta.y * SPEED);
	return p;
}

void Sprite::render() {
	if (region)
		Drawable::render();
	if (drawDebug)
		rect.drawDebugBox();
}

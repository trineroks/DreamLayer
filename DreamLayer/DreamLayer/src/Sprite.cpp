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

void Sprite::setTextureRegion(TextureRegion &tex) {
	region = &tex;
	wdraw = region->getRect().w * wscale;
	hdraw = region->getRect().h * hscale;
}

void Sprite::scaleSprite(float w, float h) {
	wdraw *= w;
	hdraw *= h;
}

void Sprite::scale(float w, float h) {
	wdraw *= w;
	hdraw *= h;
	rect.w *= w;
	rect.h *= h;

	xoffset *= w;
	yoffset *= h;
	collxOffset *= w;
	collyOffset *= h;

	wscale = w;
	hscale = h;
}

void Sprite::setCustomOrientationType(int _xoffset, int _yoffset, int _collxOffset, int _collyOffset) {
	xoffset = _xoffset;
	yoffset = _yoffset;;
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
		yoffset = hdraw / 2;;
		collxOffset = rect.w / 2;
		collyOffset = rect.h / 2;
		break;
	case BOTTOMCENTER:
		xoffset = wdraw / 2;
		yoffset = hdraw;;
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

	xdraw = (int)pos.x - xoffset;
	ydraw = (int)pos.y - yoffset;
	rect.setPos((int)pos.x - collxOffset, (int)pos.y - collyOffset);
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
	if (region)
		TextureManager::drawResized(*region, xdraw, ydraw, wdraw, hdraw, angle, xoffset, yoffset);
	if (drawDebug)
		rect.drawDebugBox();
}

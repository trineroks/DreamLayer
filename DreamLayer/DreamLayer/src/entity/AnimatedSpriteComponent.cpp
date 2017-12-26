#include "AnimatedSpriteComponent.h"



AnimatedSpriteComponent::AnimatedSpriteComponent(TransformComponent* _transform, Animation* _animation, const char* str)
	: transform(_transform) {
	x = _transform->pos.x;
	y = _transform->pos.y;

	animations.emplace(str, _animation);
	play(_animation, true);
}

AnimatedSpriteComponent::AnimatedSpriteComponent(TransformComponent* _transform, Animation* _animation, const char* str, float _speed)
	: transform(_transform) {
	x = _transform->pos.x;
	y = _transform->pos.y;

	animations.emplace(str, _animation);
	speed = _speed;
	play(_animation, true);
}

AnimatedSpriteComponent::~AnimatedSpriteComponent() {
	animations.clear();
}

void AnimatedSpriteComponent::play(const char* str, bool _loop) {
	loop = _loop;
	curr = animations.at(str);
	currFrame = 0;
	frames = curr->getSize();
}

void AnimatedSpriteComponent::play(Animation* _animation, bool _loop) {
	loop = _loop;
	curr = _animation;
	currFrame = 0;
	frames = curr->getSize();
}

void AnimatedSpriteComponent::addAnimation(Animation* animation, const char* str) {
	animations.emplace(str, animation);
}

void AnimatedSpriteComponent::update(float delta) {
	currTime += delta;
	if (currTime >= speed) {
		int frameIncrease = (int)currTime / (int)speed;
		currTime = 0;
		if (currFrame >= frames - 1) {
			if (loop)
				currFrame = 0;
			else
				currFrame = frames - 1;
		}
		else {
			currFrame += frameIncrease;
		}
	}
}

void AnimatedSpriteComponent::draw() {
	float wfinal = (float)curr->getFrame(currFrame).getRect().w * w;
	float hfinal = (float)curr->getFrame(currFrame).getRect().h * h;

	float xfinal, yfinal;

	if (transform->orientCenterFloor) {
		yfinal = transform->pos.y - hfinal;
		xfinal = transform->pos.x - (wfinal * 0.5f);
	}
	else {
		yfinal = transform->pos.y;
		xfinal = transform->pos.x;
	}

	TextureManager::drawResized(&curr->getFrame(currFrame), (int)xfinal, (int)yfinal, (int)wfinal, (int)hfinal);
}

void AnimatedSpriteComponent::scale(float _w, float _h) {
	w = _w;
	h = _h;
}

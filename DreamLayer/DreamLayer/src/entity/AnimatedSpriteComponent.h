#pragma once
#include "Components.h"
#include "../Animation.h"
#include <map>

class TransformComponent;
class AnimatedSpriteComponent {
public:
	AnimatedSpriteComponent(TransformComponent* _transform, Animation* _animation, const char* str);
	AnimatedSpriteComponent(TransformComponent* _transform, Animation* _animation, const char* str, float _speed);
	~AnimatedSpriteComponent();

	void play(const char* str, bool _loop);
	void play(Animation* _animation, bool _loop);
	void addAnimation(Animation* animation, const char* str);
	void draw();

	void scale(float _w, float _h);

private:
	void update(float delta);

	TransformComponent* transform;
	Animation* curr;
	std::map<const char*, Animation*> animations;

	float w = 1.0f;
	float h = 1.0f;

	float x, y;

	bool loop = true;
	float speed = 100.0f;
	float currTime = 0.0f;
	int frames = 0;
	int currFrame = 0;
};


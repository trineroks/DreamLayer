#pragma once
#include "../Vector2D.h"

class TransformComponent {
public:
	Vector2D pos;
	Vector2D velocity;

	//Toggle this on if we want sprites and collision rects to be based off center bottom of the entity
	bool orientCenterFloor = false;
	int speed = 2;

	TransformComponent() {
		pos.x = 0.0f;
		pos.y = 0.0f;
	}

	TransformComponent(float x, float y) {
		pos.x = x;
		pos.y = y;
	}

	void init() {
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() {
		pos.x += velocity.x * speed;
		pos.y += velocity.y * speed;
	}
};
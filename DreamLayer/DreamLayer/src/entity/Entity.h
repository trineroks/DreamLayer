#pragma once
#include "../Rect.h"
#include "Components.h"

class Entity {
public:
	Entity();
	~Entity();

private:
	AnimatedSpriteComponent* animatedSpriteComponent = nullptr;
	SpriteComponent* spriteComponent = nullptr;
	TransformComponent* transformComponent = nullptr;
};


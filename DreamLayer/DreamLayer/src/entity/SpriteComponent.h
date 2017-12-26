#pragma once
//#include "Components.h"'
#include "TransformComponent.h"
#include "../TextureRegion.h"
#include "../TextureManager.h"

class TransformComponent;
class SpriteComponent {
private:
	TransformComponent* transform;
	TextureRegion* region;

public:

	SpriteComponent(TransformComponent* _transform, TextureRegion* _region) {
		transform = _transform;
		region = _region;
	}

	void draw() {
		TextureManager::draw(region, transform->pos.x, transform->pos.y);
	}

};
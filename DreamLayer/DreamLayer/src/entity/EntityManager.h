#pragma once
#include "Components.h"
#include "../Constants.h"

class EntityManager {
public:
	EntityManager();
	~EntityManager();
	void update();

private:
	TransformComponent* transformComponents = new TransformComponent[MAX_ENTITIES];
};


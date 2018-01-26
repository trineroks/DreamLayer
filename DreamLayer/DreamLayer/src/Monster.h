#pragma once
#include "Sprite.h"
#include "Map.h"
#include "Constants.h"
#include "AStarPathfind.h"
#include <queue>

class Map;
class Monster : public Sprite {
public:
	Monster(TextureRegion &texRegion);
	~Monster();

	void generateWaypoints(Map* map);
	void update(Map* map);

	Point getMapPosition() {
		return mapPosition;
	}

private:
	Point mapPosition;
	std::queue<Point> wayPoints;
};


#pragma once
#include "Sprite.h"
#include "Map.h"
#include "Constants.h"
#include <queue>

class Map;
class Monster : public Sprite {
public:
	Monster(TextureRegion &texRegion);
	Monster() {};
	~Monster();

	void generateWaypoints(Map* map, Point p);
	void update(Map* map);
	void updateSprite();

	Point getMapPosition() {
		return mapPosition;
	}

private:
	Point currentMoveOrder = Point();
	Point mapPosition;
	std::queue<Point> wayPoints;
	//eliminate this second one soon
	std::queue<Point> moveWayPoints;
};


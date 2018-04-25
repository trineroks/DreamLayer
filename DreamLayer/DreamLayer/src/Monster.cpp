#include "Monster.h"
#include <stack>


Monster::Monster(TextureRegion &texRegion) : Sprite(texRegion)
{
}


Monster::~Monster() {
}

void clearQueue(std::queue<Point> &_wayPoints) {
	std::queue<Point> empty;
	std::swap(_wayPoints, empty);
}

void Monster::updateSprite() {
	Sprite::update();
}

void Monster::update(Map* map) {
	Sprite::update();
	mapPosition = map->getPositionInMap(pos.x, pos.y);
	if (!moveWayPoints.empty()) {
		Point delt = map->getPixelPositionInMap(moveWayPoints.front().x, moveWayPoints.front().y);
		int deltx = delt.x - (int)pos.x;
		int delty = delt.y - (int)pos.y;
		if (deltx != 0) {
			deltx = (deltx < 0) ? -1 : 1;
			delta.x = deltx * 2.0f;
		}
		if (delty != 0) {
			delty = (delty < 0) ? -1 : 1;
			delta.y = delty * 2.0f;
		}
		if (delty != 0 && deltx != 0) {
			delta.y = delty * sqrt(2.0f);
			delta.x = deltx * sqrt(2.0f);
		}
		if (map->isWithinTileVicinity(Point((int)pos.x, (int)pos.y), moveWayPoints.front())) {
			moveWayPoints.pop();
		}
		else
			printf("\n");
	}
	else {
		delta.x = 0;
		delta.y = 0;
	}
}

void Monster::generateWaypoints(Map* map, Point p) {
	map->resetPaths();
	std::stack<Point> path;
	map->getPath(mapPosition, p, *this, path);
	clearQueue(wayPoints);
	clearQueue(moveWayPoints);
	while (!path.empty()) {
		wayPoints.push(path.top());
		moveWayPoints.push(path.top());
		path.pop();
	}
	while (!wayPoints.empty()) {
		Point p = wayPoints.front();
		map->getTerrainAtTerrains(p)->testPath = true;
		wayPoints.pop();
	}
}

#include "Monster.h"
#include <stack>


Monster::Monster(TextureRegion &texRegion) : Sprite(texRegion)
{
}


Monster::~Monster() {
}

void Monster::update(Map* map) {
	Sprite::update();
	mapPosition = map->getPositionInMap(pos.x, pos.y);
}

void Monster::generateWaypoints(Map* map, Point p) {
	map->resetPaths();
	std::stack<Point> path;
	map->getPath(mapPosition, p, *this, path);
	while (!path.empty()) {
		wayPoints.push(path.top());
		path.pop();
	}
	while (!wayPoints.empty()) {
		Point p = wayPoints.front();
		map->getTerrainAtTerrains(p)->testPath = true;
		wayPoints.pop();
	}
}

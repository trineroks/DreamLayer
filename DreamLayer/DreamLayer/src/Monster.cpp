#include "Monster.h"



Monster::Monster(TextureRegion &texRegion) : Sprite(texRegion)
{

}


Monster::~Monster() {
}

void Monster::update(Map* map) {
	Sprite::update();
	mapPosition = map->getPositionInMap(pos.x, pos.y);
}

void Monster::generateWaypoints(Map* map) {
	//AStarPathfind::findPath(*map, )
}

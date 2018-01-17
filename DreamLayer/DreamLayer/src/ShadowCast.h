#pragma once
#include "Constants.h"

class Map;
class ShadowCast {
public:
	ShadowCast() {};
	void setMap(Map &_map) {
		map = &_map;
	}
	void computeVisibleCells(Point start, int _range);
private:
	void scanOctant(int octant, int depth, Point start, Point startSlopeVector, double endSlope);
	void scanOctantTest(int octant, int depth, Point start, double startSlope, double endSlope);
	bool isPointValid(Point p);
	int range = 0;
	Point start;
	Map* map;
};


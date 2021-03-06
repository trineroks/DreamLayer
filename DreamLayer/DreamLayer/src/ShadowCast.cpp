#include "ShadowCast.h"
#include "Map.h"

int getDistanceSquared(int x1, int y1, int x2, int y2);
double getSlope(double x1, double y1, double x2, double y2, bool invert);

void ShadowCast::computeVisibleCellsGradient(Point start, int _range) {
	map->setVisibilityAt(start.x, start.y);
	for (int i = 0; i < 8; i++) {
		scanOctant(i, 1, start, 1.0, 0.0, _range);
	}
}

//    \ 2 | 1 /
//   3 \  |  / 0
//   -----+-----
//   4 /  |  \ 7
//    / 5 | 6 \

void ShadowCast::scanOctant(int octant, int depth, Point start, double startSlope, double endSlope, int range) {
	int x = 0;
	int y = 0;
	int quotient = 0;
	int remainder = 0;
	switch (octant) {
	case 0:
		//we will only scan octant 0 for now.
		x = start.x + depth;
		//start y from the topmost cell, and scan downward
		y = start.y - (int)(startSlope * (double)depth);
		if (x >= map->getLightMapW())
			return;
		if (y < 0)
			y = 0;
		while (getSlope((double)x, (double)y, (double)start.x, (double)start.y, false) <= endSlope) {
			if (getDistanceSquared(x, y, start.x, start.y) <= (range * range)) {
				bool t = map->getLightMapValueAt(x, y);
				//If the current terrain is an obstacle
				if (t) {
					//If the previous terrain was not an obstacle
					if (y - 1 >= 0 && !map->getLightMapValueAt(x, y - 1))
						scanOctant(octant, depth + 1, start, startSlope, getSlope((double)x - 0.5, (double)y - 0.5, start.x, start.y, false), range);
				}
				//If the current terrain is NOT an obstacle
				else {
					//If the previous terrain was an obstacle
					if (y - 1 >= 0 && map->getLightMapValueAt(x, y - 1)) {
						startSlope = -getSlope((double)x + 0.5, (double)y - 0.5, start.x, start.y, false);
					}
				}
				map->setVisibilityAt(x, y);
			}
			y++;
		}
		y--;
		break;
	case 1:
		y = start.y - depth;
		x = start.x + (int)(startSlope * (double)depth);
		if (y < 0)
			return;
		if (x >= map->getLightMapW())
			x = map->getLightMapW() - 1;
		while (getSlope((double)x, (double)y, (double)start.x, (double)start.y, true) <= endSlope) {
			if (getDistanceSquared(x, y, start.x, start.y) <= (range * range)) {
				bool t = map->getLightMapValueAt(x, y);
				if (t) {
					if (x + 1 < map->getLightMapW() && !map->getLightMapValueAt(x + 1, y))
						scanOctant(octant, depth + 1, start, startSlope, getSlope((double)x + 0.5, (double)y + 0.5, start.x, start.y, true), range);
				}
				else {
					if (x + 1 < map->getLightMapW() && map->getLightMapValueAt(x + 1, y)) {
						startSlope = -getSlope((double)x + 0.5, (double)y - 0.5, start.x, start.y, true);
					}
				}
				map->setVisibilityAt(x, y);
			}
			x--;
		}
		x++;
		break;
	case 2:
		y = start.y - depth;
		x = start.x - (int)(startSlope * (double)depth);
		if (y < 0)
			return;
		if (x < 0)
			x = 0;
		while (getSlope((double)x, (double)y, (double)start.x, (double)start.y, true) >= endSlope) {
			if (getDistanceSquared(x, y, start.x, start.y) <= (range * range)) {
				bool t = map->getLightMapValueAt(x, y);
				if (t) {
					if (x - 1 >= 0 && !map->getLightMapValueAt(x - 1, y))
						scanOctant(octant, depth + 1, start, startSlope, getSlope((double)x - 0.5, (double)y + 0.5, start.x, start.y, true), range);
				}
				else {
					if (x - 1 >= 0 && map->getLightMapValueAt(x - 1, y)) {
						startSlope = getSlope((double)x - 0.5, (double)y - 0.5, start.x, start.y, true);
					}
				}
				map->setVisibilityAt(x, y);
			}
			x++;
		}
		x--;
		break;
	case 3:
		x = start.x - depth;
		y = start.y - (int)(startSlope * (double)depth);
		if (x < 0)
			return;
		if (y < 0)
			y = 0;
		while (getSlope((double)x, (double)y, (double)start.x, (double)start.y, false) >= endSlope) {
			if (getDistanceSquared(x, y, start.x, start.y) <= (range * range)) {
				bool t = map->getLightMapValueAt(x, y);
				if (t) {
					if (y - 1 >= 0 && !map->getLightMapValueAt(x, y - 1))
						scanOctant(octant, depth + 1, start, startSlope, getSlope((double)x + 0.5, (double)y - 0.5, start.x, start.y, false), range);
				}
				else {
					if (y - 1 >= 0 && map->getLightMapValueAt(x, y - 1)) {
						startSlope = getSlope((double)x - 0.5, (double)y - 0.5, start.x, start.y, false);
					}
				}
				map->setVisibilityAt(x, y);
			}
			y++;
		}
		y--;
		break;
	case 4:
		x = start.x - depth;
		y = start.y + (int)(startSlope * (double)depth);
		if (x < 0)
			return;
		if (y >= map->getLightMapH())
			y = map->getLightMapH() - 1;
		while (getSlope((double)x, (double)y, (double)start.x, (double)start.y, false) <= endSlope) {
			if (getDistanceSquared(x, y, start.x, start.y) <= (range * range)) {
				bool t = map->getLightMapValueAt(x, y);
				if (t) {
					if (y + 1 < map->getLightMapH() && !map->getLightMapValueAt(x, y + 1))
						scanOctant(octant, depth + 1, start, startSlope, getSlope((double)x + 0.5, (double)y + 0.5, start.x, start.y, false), range);
				}
				else {
					if (y + 1 < map->getLightMapH() && map->getLightMapValueAt(x, y + 1)) {
						startSlope = -getSlope((double)x - 0.5, (double)y + 0.5, start.x, start.y, false);
					}
				}
				map->setVisibilityAt(x, y);
			}
			y--;
		}
		y++;
		break;
	case 5:
		y = start.y + depth;
		x = start.x - (int)(startSlope * (double)depth);
		if (y >= map->getLightMapH())
			return;
		if (x < 0)
			x = 0;
		while (getSlope((double)x, (double)y, (double)start.x, (double)start.y, true) <= endSlope) {
			if (getDistanceSquared(x, y, start.x, start.y) <= (range * range)) {
				bool t = map->getLightMapValueAt(x, y);
				if (t) {
					if (x - 1 >= 0 && !map->getLightMapValueAt(x - 1, y))
						scanOctant(octant, depth + 1, start, startSlope, getSlope((double)x - 0.5, (double)y - 0.5, start.x, start.y, true), range);
				}
				else {
					if (x - 1 >= 0 && map->getLightMapValueAt(x - 1, y)) {
						startSlope = -getSlope((double)x - 0.5, (double)y + 0.5, start.x, start.y, true);
					}
				}
				map->setVisibilityAt(x, y);
			}
			x++;
		}
		x--;
		break;
	case 6:
		y = start.y + depth;
		x = start.x + (int)(startSlope * (double)depth);
		if (y >= map->getLightMapH())
			return;
		if (x >= map->getLightMapW())
			x = map->getLightMapW() - 1;
		while (getSlope((double)x, (double)y, (double)start.x, (double)start.y, true) >= endSlope) {
			if (getDistanceSquared(x, y, start.x, start.y) <= (range * range)) {
				bool t = map->getLightMapValueAt(x, y);
				if (t) {
					if (x + 1 < map->getLightMapW() && !map->getLightMapValueAt(x + 1, y))
						scanOctant(octant, depth + 1, start, startSlope, getSlope((double)x + 0.5, (double)y - 0.5, start.x, start.y, true), range);
				}
				else {
					if (x + 1 < map->getLightMapW() && map->getLightMapValueAt(x + 1, y)) {
						startSlope = getSlope((double)x + 0.5, (double)y + 0.5, start.x, start.y, true);
					}
				}
				map->setVisibilityAt(x, y);
			}
			x--;
		}
		x++;
		break;
	case 7:
		x = start.x + depth;
		y = start.y + (int)(startSlope * (double)depth);
		if (x >= map->getLightMapW())
			return;
		if (y >= map->getLightMapH())
			y = map->getLightMapH() - 1;
		while (getSlope((double)x, (double)y, (double)start.x, (double)start.y, false) >= endSlope) {
			if (getDistanceSquared(x, y, start.x, start.y) <= (range * range)) {
				bool t = map->getLightMapValueAt(x, y);
				if (t) {
					if (y + 1 < map->getLightMapH() && !map->getLightMapValueAt(x, y + 1))
						scanOctant(octant, depth + 1, start, startSlope, getSlope((double)x - 0.5, (double)y + 0.5, start.x, start.y, false), range);
				}
				else {
					if (y + 1 < map->getLightMapH() && map->getLightMapValueAt(x, y + 1)) {
						startSlope = getSlope((double)x + 0.5, (double)y + 0.5, start.x, start.y, false);
					}
				}
				map->setVisibilityAt(x, y);
			}
			y--;
		}
		y++;
		break;
	}

	if (x < 0)
		x = 0;
	else if (x >= map->getLightMapW())
		x = map->getLightMapW() - 1;

	if (y < 0)
		y = 0;
	else if (y >= map->getLightMapH())
		y = map->getLightMapH() - 1;
	//This check is necessary so that we don't have the artifacting of seeing through walls when at level with an obstacle
	if (depth < range - 1 && !map->getLightMapValueAt(x, y))
		scanOctant(octant, depth + 1, start, startSlope, endSlope, range);
}

//Gets the distance between two points squared. 
//This will have to be compared to rangeSquared so as to keep
//everything neatly in integers
int getDistanceSquared(int x1, int y1, int x2, int y2) {
	return ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2));
}

//Get slope. We use double to maintain accuracy.
double getSlope(double x1, double y1, double x2, double y2, bool invert) {
	if (invert)
		return ((x1 - x2) / (y1 - y2));
	else
		return ((y1 - y2) / (x1 - x2));	
}
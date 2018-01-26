#pragma once
#include "Map.h"
#include "Sprite.h"
#include <stack>

class Node {
public:
	Node(Point _p, int _g) : p(_p), g(_g) {}
	Node() {
	}
	Point p;
	float g = 0.0f;
	float f = 0.0f;
	Node* parent = nullptr;
};

class AStarPathfind {
public:
	Point directions[8] = { Point(0,-1), Point(0, 1), Point(-1, 0), Point(1, 0),
							Point(-1, -1), Point(1, 1), Point(1, -1), Point(-1, 1)};
	AStarPathfind() {};
	bool findPath(Map& map, Point start, Point dest, std::stack<Point>& finalPath, Sprite& sprite);
private:
	void getNeighbors(Node* n, Node* neighbors, Map& map, Sprite& sprite);
};


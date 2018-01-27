#pragma once
#include "Sprite.h"
#include <stack>
#include <set>

class Map;
class Node {
public:
	Node(Point _p, float _g) : p(_p), g(_g) {}
	Node() {
	}
	Point p;
	float g = 0.0f;
	float f = 0.0f;
	Node* parent = nullptr;
	bool operator<(const Node &n) const {
		return this->f < n.f;
	}
};

using NodeSet = std::set<Node*>;

class AStarPathfind {
public:
	Point directions[8] = { Point(0,-1), Point(0, 1), Point(-1, 0), Point(1, 0),
							Point(-1, -1), Point(1, 1), Point(1, -1), Point(-1, 1)};
	AStarPathfind() {};
	bool findPath(Point start, Point dest, std::stack<Point>& finalPath, Sprite& sprite);
	void testFunction();
	void setMap(Map &_map) {
		map = &_map;
	}
private:
	void getNeighbors(Node* n, Node* neighbors, Sprite& sprite);
	void freeNodeList(NodeSet& n);
	Map* map;
};


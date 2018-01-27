#include "AStarPathfind.h"
#include <queue>
#include <vector>
#include <functional>
#include <math.h>
#include <stdio.h>
#include "Map.h"

//Cost of moving non-diagonally
const static float ND = 1.0f;
//Cost of moving diagonally (sqrt(2))
const static float D = 1.414f;

//Diagonal distance heuristic from http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
float heuristic(Point p, Point goal) {
	int dx = std::abs(p.x - goal.x);
	int dy = std::abs(p.y - goal.y);
	return ND * std::max(dx, dy) + (D - 1) * std::min(dx, dy);
}

void generatePath(Node& n, std::stack<Point>& finalPath) {
	finalPath.push(n.p);
	Node* curr;
	curr = &n;
	while (curr->parent != nullptr) {
		curr = curr->parent;
		finalPath.push(curr->p);
	}
	return;
}

void AStarPathfind::getNeighbors(Node* n, Node* neighbors, Sprite& sprite) {
	Point p = n->p;
	for (int i = 0; i < 8; i++) {
		Point p1 = Point(p.x + directions[i].x, p.y + directions[i].y);
		if (map->isTileTraversableAI(p, p1, sprite)) {
			if (i < 4)
				neighbors[i] = Node(p1, n->g + ND);
			else
				neighbors[i] = Node(p1, n->g + D);
			neighbors[i].parent = n;
		}
		else {
			neighbors[i] = Node(Point(-1, -1), -1);
		}
	}
}

Node* findNodeInList(NodeSet &set, Point p) {
	for (auto node : set) {
		if (node->p == p) {
			return node;
		}
	}
	return nullptr;
}

void AStarPathfind::freeNodeList(NodeSet& n) {
	for (auto node = n.begin(); node != n.end();) {
		delete *node;
		node = n.erase(node);
	}
}

bool AStarPathfind::findPath(Point start, Point dest, std::stack<Point>&finalPath, Sprite& sprite) {
	int width = map->getWidth();
	int height = map->getHeight();
	bool found = false;

	NodeSet openList;
	NodeSet closedList;
	
	Node* startNode = new Node(start, 0);

	startNode->f = startNode->g + heuristic(start, dest);

	openList.insert(startNode);

	while (!openList.empty()) {
		Node* curr = *openList.begin();
		for (auto node : openList) {
			if (node->f <= curr->f) {
				curr = node;
			}
		}
		if (curr->p == dest) {
			generatePath(*curr, finalPath);
			found = true;
			break;
		}
		openList.erase(std::find(openList.begin(), openList.end(), curr));
		closedList.insert(curr);
		for (int i = 0; i < 8; i++) {
			Point p1 = Point(curr->p.x + directions[i].x, curr->p.y + directions[i].y);
			if (map->isTileTraversableAI(curr->p, p1, sprite) && findNodeInList(closedList, p1) == nullptr) {
				float gCost = curr->g + ((i < 4) ? ND : D);
				Node* successor = findNodeInList(openList, p1);
				if (successor == nullptr) {
					successor = new Node(p1, gCost);
					successor->parent = curr;
					successor->f = gCost + heuristic(p1, dest);
					openList.insert(successor);
				}
				else if (gCost < successor->g) {
					successor->g = gCost;
					successor->parent = curr;
				}
			}
		}
	}
	//remember to deallocate memory!
	freeNodeList(openList);
	freeNodeList(closedList);

	return found;
}
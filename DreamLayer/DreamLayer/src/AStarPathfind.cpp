#include "AStarPathfind.h"
#include <queue>
#include <vector>
#include <functional>
#include <math.h>
#include <set>

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

bool operator<(const Node &n1, const Node &n2) {
	return n1.f < n2.f;
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

void AStarPathfind::getNeighbors(Node* n, Node* neighbors, Map& map, Sprite& sprite) {
	Point p = n->p;
	for (int i = 0; i < 8; i++) {
		Point p1 = Point(p.x + directions[i].x, p.y + directions[i].y);
		if (map.isTileTraversableAI(p, p1, sprite)) {
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

using NodeSet = std::set<Node*>;

Node* findNodeInList(NodeSet &set, Point p) {
	for (auto node : set) {
		if (node->p == p) {
			return node;
		}
	}
	return nullptr;
}


bool AStarPathfind::findPath(Map& map, Point start, Point dest, std::stack<Point>&finalPath, Sprite& sprite) {
	int width = map.getWidth();
	int height = map.getHeight();
	bool found = false;

	NodeSet openList;
	NodeSet closedList;
	
	Node startNode(start, 0);
	Node goalNode(dest, 0);

	startNode.f = startNode.g + heuristic(start, dest);

	openList.insert(&startNode);

	Node* neighbors = new Node[8];

	while (!openList.empty()) {
		Node* curr = *openList.begin();
		if (curr->p == dest) {
			generatePath(*curr, finalPath);
			found = true;
			break;
		}
		openList.erase(std::find(openList.begin(), openList.end(), curr));
		closedList.insert(curr);
		getNeighbors(curr, neighbors, map, sprite);
		for (int i = 0; i < 8; i++) {
			//its x/y would not be negative if it was a valid neighbor
			Point neighborPoint = neighbors[i].p;
			if (neighborPoint.x >= 0 && findNodeInList(closedList, neighborPoint) == nullptr) {
				neighbors[i].f = neighbors[i].g + heuristic(neighbors[i].p, dest);
				Node *successor = findNodeInList(openList, neighborPoint);
				if (successor == nullptr) {
					openList.insert(&neighbors[i]);
				}
				else if (neighbors[i].g < successor->g) {
					successor->g = neighbors[i].g;
					successor->parent = neighbors[i].parent;
				}
			}
		}
	}
	//remember to deallocate memory!
	delete[] neighbors;
	return found;
}
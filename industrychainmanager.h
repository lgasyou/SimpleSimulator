#ifndef INDUSTRYCHAINMANAGER_H
#define INDUSTRYCHAINMANAGER_H

class BaseBuilding;

struct Edge {
	Edge(int cost_, Edge *nextEdge_) :
		cost(cost_),
		nextEdge(nextEdge_) { }

	int cost;
	Edge *nextEdge;
};

struct Vertex {
	BaseBuilding *building;
	Edge *firstEdge;
};

// This class contains the industry chain of this game.
class IndustryChainManager {
public:
	static IndustryChainManager &instance();

	int distance(BaseBuilding *, BaseBuilding *);

	void addPath(BaseBuilding *, BaseBuilding *, int);

private:
	IndustryChainManager();;
	~IndustryChainManager();
	IndustryChainManager(const IndustryChainManager &) = delete;
	IndustryChainManager &operator=(const IndustryChainManager &) = delete;
};
#endif // !INDUSTRYCHAINMANAGER_H

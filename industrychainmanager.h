#ifndef INDUSTRYCHAINMANAGER_H
#define INDUSTRYCHAINMANAGER_H

#include <vector>
#include "graph.h"

class BaseBuilding;
struct Goods;

class QString;

// This class contains the industry chain of this game.
class IndustryChainManager {
public:
	static IndustryChainManager &instance();

	void init();

	// Returns the cost from origin to destination.
	double cost(const QString &orig, const QString &dest) const;

	std::vector<Goods> precursors(const QString &item) const;

	std::vector<Goods> successors(const QString &item) const;

private:
	IndustryChainManager();
	~IndustryChainManager();
	IndustryChainManager(const IndustryChainManager &) = delete;
	IndustryChainManager &operator=(const IndustryChainManager &) = delete;

	Graph industryChain_;
};
#endif // !INDUSTRYCHAINMANAGER_H

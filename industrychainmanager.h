#ifndef INDUSTRYCHAINMANAGER_H
#define INDUSTRYCHAINMANAGER_H

#include <vector>
#include <QString>
#include "graph.h"

class BaseBuilding;
struct Goods;

// This class contains the industry chain of this game.
class IndustryChainManager {
public:
	static IndustryChainManager &instance();

	void init();

	double cost(const QString &beg, const QString &end) const;

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

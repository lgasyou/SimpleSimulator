#include "industrychainmanager.h"

IndustryChainManager::IndustryChainManager() {
	init();
}

IndustryChainManager::~IndustryChainManager() { }

void IndustryChainManager::init() {
	// TODO
	// Move this into a file like .xml
	// then just read file.
	industryChain_.addPath("Coal", "Steel", 2);
	industryChain_.addPath("Iron", "Steel", 1);
	industryChain_.addPath("Log", "Plank", 0.5);
	industryChain_.addPath("Steel", "Product", 0.5);
	industryChain_.addPath("Plank", "Product", 1);
}

IndustryChainManager &IndustryChainManager::instance() {
	static IndustryChainManager industryChainManager;
	return industryChainManager;
}

double IndustryChainManager::cost(const QString &beg, const QString &end) const {
	return industryChain_.volume(beg, end);
}

std::vector<Goods> IndustryChainManager::precursors(const QString &item) const {
	return industryChain_.precursors(item);
}

std::vector<Goods> IndustryChainManager::successors(const QString &item) const {
	return industryChain_.successors(item);
}

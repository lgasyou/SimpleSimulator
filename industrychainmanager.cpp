#include "industrychainmanager.h"

IndustryChainManager::IndustryChainManager() { }

IndustryChainManager::~IndustryChainManager() { }

IndustryChainManager &IndustryChainManager::instance() {
	static IndustryChainManager industryChainManager;
	return industryChainManager;
}
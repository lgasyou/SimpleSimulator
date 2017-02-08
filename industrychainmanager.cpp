#include "industrychainmanager.h"

IndustryChainManager::IndustryChainManager() { }

IndustryChainManager::~IndustryChainManager() { }

IndustryChainManager &IndustryChainManager::instance() {
	static IndustryChainManager industryChainManager;
	return industryChainManager;
}

int IndustryChainManager::distance(BaseBuilding *start, BaseBuilding *dest) {
	return 0;
}

void IndustryChainManager::addPath(BaseBuilding *start, BaseBuilding *dest, int distance) {
	//for (auto &vertex : map_) {
	//	if (vertex.building == start) {
	//		Edge *p = vertex.firstEdge->nextEdge;
	//		vertex.firstEdge->nextEdge = new Edge(distance, p);
	//		break;
	//	}
	//}
}

#include "mapmanager.h"

MapManager::MapManager() {
	init();
}

MapManager::~MapManager() { }

MapManager &MapManager::instance() {
	static MapManager mapManager;
	return mapManager;
}

void MapManager::init() {

}
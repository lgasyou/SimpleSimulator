#include "mapmanager.h"
#include "basebuilding.h"

#include "vector2d.h"
#include "valuegenerator.h"

MapManager::MapManager() { }

MapManager::~MapManager() { }

MapManager &MapManager::instance() {
	static MapManager mapManager;
	return mapManager;
}

void MapManager::init() {
	for (int x = 0; x != 16; ++x)
		for (int y = 0; y != 16; ++y)
			occupiedMap_[x][y] = false;
}

Vector2D MapManager::allocate() {
	int x = 0;
	int y = 0;
	do {
		do {
			x = ValueGenerator::instance().uniformDistribution(0, 15);
		} while (x < 0 || x > 15);
		do {
			y = ValueGenerator::instance().uniformDistribution(0, 15);
		} while (y < 0 || y > 15);
	} while (occupiedMap_[x][y]);
	occupiedMap_[x][y] = true;
	return Vector2D(x, y);
}
#include "mapmanager.h"
#include "basebuilding.h"

#include "vector2d.h"
#include "valuegenerator.h"

MapManager::MapManager() {
	init();
}

MapManager::~MapManager() { }

MapManager &MapManager::instance() {
	static MapManager mapManager;
	return mapManager;
}

void MapManager::init() {
	for (int x = 0; x != 100; ++x)
		for (int y = 0; y != 100; ++y)
			occupiedMap_[x][y] = false;
}

Vector2D MapManager::allocate() {
	int x = 0;
	int y = 0;
	do {
		do {
			x = ValueGenerator::instance().uniformDistribution(0, 99);
		} while (x < 0 || x > 99);
		do {
			y = ValueGenerator::instance().uniformDistribution(0, 99);
		} while (y < 0 || y > 99);
	} while (occupiedMap_[x][y]);
	occupiedMap_[x][y] = true;
	return Vector2D(x, y);
}
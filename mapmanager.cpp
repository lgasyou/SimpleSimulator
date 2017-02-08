#include "mapmanager.h"
#include "vector2d.h"
#include "basebuilding.h"

MapManager::MapManager() {
	init();
}

MapManager::~MapManager() { }

MapManager &MapManager::instance() {
	static MapManager mapManager;
	return mapManager;
}

void MapManager::init() {
	for (int i = 0; i != 100; ++i)
		for (int j = 0; j != 100; ++j)
			occupiedMap_[i][j] = false;
	firstFree = Vector2D(0.0, 0.0);
}

Vector2D MapManager::allocate() {
	int x = firstFree.x();
	int y = firstFree.y();

	if (x == 100)
		return Vector2D();
	if (y == 99) {
		firstFree.setX(x + 1);
		firstFree.setY(0);
	} else {
		firstFree.setY(y + 1);
	}
	occupiedMap_[x][y] = true;
	return Vector2D(x, y);
}
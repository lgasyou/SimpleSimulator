#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "vector2d.h"

// This class creates a map which contains all buildings.
// This class is designed for working with transportations modules.
class MapManager {
public:
	static MapManager &instance();

	void init();

	Vector2D allocate();

private:
	MapManager();
	~MapManager();
	MapManager(const MapManager &) = delete;
	MapManager &operator=(const MapManager &) = delete;

	bool occupiedMap_[100][100];
	Vector2D firstFree;
};
#endif // !MAPMANAGER_H

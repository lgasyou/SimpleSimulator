#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "gameconstants.h"

class BaseBuilding;
class Vector2D;

struct MapNode {
	bool isOccupied;

	GameConstants::BuildingTypes buildingType;
};



// This class creates a map which contains all buildings.
// This class is designed for working with transportations modules.
class MapManager {
public:
	// Use singleton pattern.
	static MapManager &instance();

	void init();

	// Allocates and returns a coordinate with ValueGenerator.
	// TODO:
	// It still has some performance issues. It'll generate many 
	// useless data if the map is almost full.
	Vector2D allocate();

	auto occupiedMap() const -> const bool(*)[100];

private:
	// Hide constructor and destructor.
	MapManager();

	~MapManager();

	MapManager(const MapManager &) = delete;

	MapManager &operator=(const MapManager &) = delete;

private:
	// This array contains a map which shows whether a location is
	// occupied or not.
	bool occupiedMap_[100][100];
};

inline auto MapManager::occupiedMap() const -> const bool(*)[100] {
	return this->occupiedMap_;
}

#endif // !MAPMANAGER_H

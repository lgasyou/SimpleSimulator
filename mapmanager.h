#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <vector>

class BaseBuilding;

namespace Map {

struct Edge {
	int length;
	Edge *nextEdge;
};

struct Vertex {
	BaseBuilding *building;
	Edge *firstEdge;
};

}


// This class creates a map which contains all buildings.
// This class is designed for working with transportations modules.
class MapManager {
public:
	static MapManager &instance();

private:
	MapManager();
	~MapManager();
	MapManager(const MapManager &) = delete;
	MapManager &operator=(const MapManager &) = delete;

	void init();

	std::vector<Map::Vertex> map_;
};
#endif // !MAPMANAGER_H

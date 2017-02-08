#ifndef MAPMANAGER_H
#define MAPMANAGER_H

class Vector2D;

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
};
#endif // !MAPMANAGER_H

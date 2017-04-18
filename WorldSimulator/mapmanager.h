/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

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

	// Allocates and returns a coordinate with Random.
	// TODO:
	// It still has some performance issues. It'll generate many 
	// useless data if the map is almost full.
	Vector2D allocate();

	auto occupiedMap() const -> const bool(*)[100]{
		return occupiedMap_;
	}

private:
	// Hide constructor and destructor.
	MapManager();

	~MapManager();

private:
	// This array contains a map which shows whether a location is
	// occupied or not.
	bool occupiedMap_[100][100];
};

#endif // !MAPMANAGER_H

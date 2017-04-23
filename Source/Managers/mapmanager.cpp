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

#include "mapmanager.h"

#include "Source/random.h"

using namespace gameconstants;

MapManager::MapManager() { }

MapManager::~MapManager() { }

MapManager &MapManager::instance() {
    static MapManager mapManager;
    return mapManager;
}

void MapManager::init() {
    for (int x = 0; x != 16; ++x)
        for (int y = 0; y != 16; ++y)
            gameMap_[x][y] = StructureType::UnusedLand;
}

Vector2D MapManager::allocate(StructureType type) {
    const int &mapHeight = gameconstants::mapHeight;
    const int &mapWeight = gameconstants::mapWeight;
    int x = 0, y = 0;
    do {
        do {
            x = Random::instance().uniformDistribution(0, mapHeight - 1);
        } while (x < 0 || x > mapHeight - 1);
        do {
            y = Random::instance().uniformDistribution(0, mapWeight - 1);
        } while (y < 0 || y > mapWeight - 1);
    } while (gameMap_[x][y] != StructureType::UnusedLand);
    gameMap_[x][y] = type;
    return Vector2D(x, y);
}
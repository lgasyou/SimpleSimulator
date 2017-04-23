/*
 *  Copyright 2017 Li Zeqing
 *
 *  This file is part of World Simulator.
 *  
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
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
    for (int x = 0; x != mapHeight; ++x)
        for (int y = 0; y != mapWeight; ++y)
            gameMap_[x][y] = StructureType::UnusedLand;
}

Vector2D MapManager::allocate(StructureType type) {
    int x = 0, y = 0;
    do {
        x = Random::instance().uniformDistribution(0, mapHeight - 1);
        y = Random::instance().uniformDistribution(0, mapWeight - 1);
    } while (gameMap_[x][y] != StructureType::UnusedLand);
    gameMap_[x][y] = type;
    return Vector2D(x, y);
}

void MapManager::setNodeType(const Vector2D &pos, gameconstants::StructureType newType) {
    int x = pos.x(), y = pos.y();
    gameMap_[x][y] = newType;
}

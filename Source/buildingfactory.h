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
 *  along with World Simulator. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BUILDINGFACTORY_H
#define BUILDINGFACTORY_H

#include <QString>

#include "gameconstants.h"
#include "Source/Objects/land.h"
#include "Source/Managers/mapmanager.h"

class BuildingFactory {
public:
    // Creates a new object and sets other parameters.
    // If position is valid, it will use it. Otherwise it'll allocate a new position.
    Land *create(gameconstants::StructureType, Vector2D position = Vector2D(-1, -1));

private:
    // Creates an instance according to buildingType;
    void createInstance(gameconstants::StructureType buildingType);

    // Generates a primitive value.
    void setBasicValue();

    void allocatePosition(gameconstants::StructureType buildingType, Vector2D position);

private:
    Land *building = nullptr;

};

inline void BuildingFactory::allocatePosition(gameconstants::StructureType buildingType, Vector2D position) {
    (position == Vector2D(-1, -1)) ?
        position = MapManager::instance().allocate(buildingType) :
        MapManager::instance().setNodeType(position, buildingType);
    building->setPosition(position);
}

#endif // !BUILDINGFACTORY_H

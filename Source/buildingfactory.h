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

#include "Source/Objects/land.h"
#include "Source/Managers/mapmanager.h"

struct LandInitialParameter {
    LandInitialParameter(StructureType type = UNUSED_LAND, const Vector2D &position = Vector2D(-1, -1), double basicValue = 0.0, double deltaValue = 0.0, LegalPerson *owner = nullptr, const QString &resource = "Unallocated")
        : type(type),
          position(position),
          basicValue(basicValue),
          deltaValue(deltaValue),
          owner(owner),
          resource(resource) {
    }

    StructureType type;
    Vector2D position;
    double basicValue;
    double deltaValue;
    LegalPerson *owner;
    QString resource;

};

class BuildingFactory {
public:
    BuildingFactory() = default;

    // Creates a new object use LandInitialParameter
    Land *create(const LandInitialParameter &landParameter);

private:
    // Creates an instance according to buildingType;
    void createInstance();

    void allocatePosition() const;

    // Generates a primitive value.
    void setValue();

    void setOwner();

    void setResource();

private:
    Land *building = nullptr;

    LandInitialParameter parameter;

};

inline void BuildingFactory::allocatePosition() const {
    Vector2D position = parameter.position;
    (position == Vector2D(-1, -1)) ?
        position = MapManager::instance().allocate(parameter.type) :
        MapManager::instance().setNodeType(position, parameter.type);
    building->setPosition(position);
}

#endif // !BUILDINGFACTORY_H

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

#include "buildingmanager.h"

#include <map>

#include "Source/buildingfactory.h"

using namespace gameconstants;

BuildingManager::BuildingManager() { }

BuildingManager::~BuildingManager() {
    for (auto building : buildings()) {
        delete building;
    }
}

BuildingManager &BuildingManager::instance() {
    static BuildingManager buildingManager;
    return buildingManager;
}

void BuildingManager::init() {
    add(Mine);
    add(Mine);
    add(Factory);
    add(Bank);
    add(Supermarket);
    add(Garage);
    for (int i = 0; i != 5; ++i)
        add(Villa);

    BuildingFactory factory;
    for (int i = 0; i != mapHeight; ++i) {
        for (int j = 0; j != mapWeight; ++j) {
            if (buildings_[i][j] == nullptr) {
                buildings_[i][j] = factory.create(LandInitialParameter{ UnusedLand, Vector2D(i,j) });
            }
        }
    }
}

StructureType BuildingManager::stringToEnum(const QString &type) {
    static std::map<QString, StructureType> stringToEnumMap{
        {"Bank", Bank },
        {"Factory", Factory },
        {"Farm", Farm },
        {"Garage", Garage },
        {"Mine", Mine },
        {"Supermarket", Supermarket },
        {"Unused Land", UnusedLand },
        {"Villa", Villa } };
    return stringToEnumMap[type];
}

void BuildingManager::add(StructureType buildingType) {
    BuildingFactory factory;
    Land *newBuilding = factory.create(LandInitialParameter{ buildingType });
    
    int x = newBuilding->position().x();
    int y = newBuilding->position().y();
    buildings_[x][y] = newBuilding;
    dataChanged_ = true;
}

const std::vector<Land *> &BuildingManager::buildings() const {
    static std::vector<Land *> buildingsBuffer;
    if (dataChanged_) {
        buildingsBuffer.clear();
        for (const auto &row : buildings_) {
            for (Land *building : row) {
                if (building->type() != "Unused Land")
                    buildingsBuffer.push_back(building);
            }
        }
        dataChanged_ = false;
    }
    return buildingsBuffer;
}

double BuildingManager::deltaValueOfCompanyProperties(Company *company) const {
    double totalDeltaValue = 0.0;
    for (const auto building : buildings()) {
        if (building->owner() == company)
            totalDeltaValue += building->deltaValue();
    }
    return totalDeltaValue;
}

std::size_t BuildingManager::buildingNumber() const {
    return buildings().size();
}

Land *BuildingManager::getById(int id) const {
    return buildings()[id];
}

Land *BuildingManager::resetType(Land *building, StructureType type) {
    BuildingFactory buildingFactory;
    Land *buildingCopy = buildingFactory.create(LandInitialParameter{
        type,
        building->position(),
        building->value(),
        building->deltaValue(),
        building->owner(),
        building->resource()
    });

    int x = building->position().x();
    int y = building->position().y();
    
    delete building;
    dataChanged_ = true;
    return buildings_[x][y] = buildingCopy;
}

void BuildingManager::update() {
    std::for_each(buildings().begin(), buildings().end(), [](Land *b) { b->update(); });
}

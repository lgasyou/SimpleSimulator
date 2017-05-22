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

#include "LandParcelManager.h"

#include <map>

#include "Source/BuildingFactory.h"

using namespace gameconstants;

LandParcelManager::LandParcelManager() { }

LandParcelManager::~LandParcelManager() {
    for (auto building : buildings()) {
        delete building;
    }
}

LandParcelManager &LandParcelManager::instance() {
    static LandParcelManager buildingManager;
    return buildingManager;
}

void LandParcelManager::init() {
    add(MINE);
    add(MINE);
    add(FACTORY);
    add(BANK);
    add(SUPERMARKET);
    add(GARAGE);
    for (int i = 0; i != 5; ++i)
        add(VILLA);

    BuildingFactory factory;
    for (int i = 0; i != mapHeight; ++i) {
        for (int j = 0; j != mapWeight; ++j) {
            if (buildings_[i][j] == nullptr) {
                buildings_[i][j] = factory.create(LandInitialParameter{ UNUSED_LAND, Vector2D(i,j) });
            }
        }
    }
}

StructureType LandParcelManager::stringToEnum(const QString &type) {
    static std::map<QString, StructureType> stringToEnumMap{
        {"Bank", BANK },
        {"Factory", FACTORY },
        {"Farm", FARM },
        {"Garage", GARAGE },
        {"Mine", MINE },
        {"Supermarket", SUPERMARKET },
        {"Unused Land", UNUSED_LAND },
        {"Villa", VILLA } };
    return stringToEnumMap[type];
}

void LandParcelManager::add(StructureType buildingType) {
    BuildingFactory factory;
    LandParcel *newBuilding = factory.create(LandInitialParameter{ buildingType });
    
    int x = newBuilding->position().x();
    int y = newBuilding->position().y();
    buildings_[x][y] = newBuilding;
    dataChanged_ = true;
}

const std::vector<LandParcel *> &LandParcelManager::buildings() const {
    static std::vector<LandParcel *> buildingsBuffer;
    if (dataChanged_) {
        buildingsBuffer.clear();
        for (const auto &row : buildings_) {
            for (LandParcel *building : row) {
                if (building->type() != "Unused Land")
                    buildingsBuffer.push_back(building);
            }
        }
        dataChanged_ = false;
    }
    return buildingsBuffer;
}

double LandParcelManager::deltaValueOfCompanyProperties(Company *company) const {
    double totalDeltaValue = 0.0;
    for (const auto building : buildings()) {
        if (building->owner() == company)
            totalDeltaValue += building->deltaValue();
    }
    return totalDeltaValue;
}

std::size_t LandParcelManager::buildingNumber() const {
    return buildings().size();
}

LandParcel *LandParcelManager::getById(int id) const {
    return buildings()[id];
}

LandParcel *LandParcelManager::changeType(LandParcel *building, StructureType type) {
    BuildingFactory buildingFactory;
    auto buildingCopy = buildingFactory.create(LandInitialParameter{
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

void LandParcelManager::update() {
    std::for_each(buildings().begin(), buildings().end(), [](LandParcel *b) { b->update(); });
}

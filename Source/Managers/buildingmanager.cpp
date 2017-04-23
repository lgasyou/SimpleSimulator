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

#include "buildingmanager.h"

#include <map>

#include "Source/buildingfactory.h"
#include "Source/random.h"

BuildingManager::BuildingManager() { }

BuildingManager::~BuildingManager() {
    for (BaseBuilding *building : buildingsTmp_) {
        delete building;
    }
}

BuildingManager &BuildingManager::instance() {
    static BuildingManager buildingManager;
    return buildingManager;
}

void BuildingManager::init() {
    using namespace gameconstants;
    add(UnusedLand);
    add(Mine);
    add(Mine);
    add(Factory);
    add(Bank);
    add(Supermarket);
    add(Garage);
    for (int i = 0; i != 5; ++i)
        add(Villa);
}

gameconstants::StructureType BuildingManager::stringToEnum(const QString &type) {
    using namespace gameconstants;
    static std::map<QString, gameconstants::StructureType> stringToEnumMap{
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

void BuildingManager::add(BaseBuilding *building) {
    buildingsTmp_.push_back(building);
}

void BuildingManager::add(gameconstants::StructureType buildingType) {
    BuildingFactory factory;
    BaseBuilding *newBuilding = factory.create(buildingType);
    this->add(newBuilding);
}

void BuildingManager::remove(BaseBuilding *building) {
    auto iter = std::find(buildingsTmp_.begin(), buildingsTmp_.end(), building);
    buildingsTmp_.erase(iter);
}

double BuildingManager::deltaValueOfCompanyProperties(Company *company) const {
    double totalDeltaValue = 0.0;
    for (auto building : buildingsTmp_) {
        if (building->owner() == company)
            totalDeltaValue += building->deltaValue();
    }
    return totalDeltaValue;
}

BaseBuilding *BuildingManager::getByPos(int x, int y) const {
    for (auto building : buildingsTmp_)
        if (building->position() == Vector2D(x, y))
            return building;
    return nullptr;
}


int BuildingManager::indexOf(BaseBuilding *building) const {
    for (std::size_t i = 0; i != buildingsTmp_.size(); ++i)
        if (buildingsTmp_[i] == building)
            return static_cast<int>(i);
    return -1;
}

BaseBuilding *BuildingManager::resetType(BaseBuilding *building, gameconstants::StructureType type) {
    BuildingFactory buildingFactory;
    BaseBuilding *buildingCopy = buildingFactory.create(type);
    buildingCopy->copyFrom(*building);

    auto iterator = std::find(buildingsTmp_.begin(), buildingsTmp_.end(), building);
    delete *iterator;
    return *iterator = buildingCopy;
}

void BuildingManager::update() {
    std::for_each(buildingsTmp_.begin(), buildingsTmp_.end(), [](BaseBuilding *building) { building->update(); });
}
#include "BuildingManager.h"
#include "ValueGenerator.h"
#include "Residence.h"
#include "Factory.h"
#include "Company.h"

BuildingManager::BuildingManager() :
    totalDeltaValue_(0)
{
    double value = ValueGenerator::normalDistribution(50, 25);
    buildingList_.push_back(new BuildingBase(value));
    for (int i = 0; i != 5; ++i) {
        double value = ValueGenerator::normalDistribution(100, 25);
        buildingList_.push_back(new Factory(value));
    }
    for (int i = 0; i != 5; ++i) {
        double value = ValueGenerator::normalDistribution(200, 36);
        buildingList_.push_back(new Residence(value));
    }
}

BuildingManager::BuildingManager(int number) :
    totalDeltaValue_(0)
{ }

BuildingBase *BuildingManager::getBuildingById(unsigned id) {
    return buildingList_[id];
}

const double BuildingManager::totalDeltaValue() {
    totalDeltaValue_ = 0;
    for (auto &building : buildingList_) {
        totalDeltaValue_ += building->deltaValue();
    }
    return totalDeltaValue_;
}

BuildingBase *BuildingManager::setItemType(BuildingBase *building, const QString &type) {
    int id = buildingList_.indexOf(building);
    BuildingBase *newBuilding = nullptr;
    if (type == "Foundation")
        newBuilding = new BuildingBase(*building);
    else if (type.contains("Factory"))
        newBuilding = new Factory(*building, type);
    else
        newBuilding = new Residence(*building);

    delete buildingList_[id];
    buildingList_.removeAt(id);
    buildingList_.insert(id, newBuilding);
    return newBuilding;
}

void BuildingManager::manage(BuildingBase *building, const QString &cmd) {
    building->manage(cmd);
}

void BuildingManager::addItem(BuildingBase *building) {
    buildingList_.push_back(building);
}

void BuildingManager::removeItem(BuildingBase *building) {
    buildingList_.removeOne(building);
}

void BuildingManager::update() {
    for (auto &building : buildingList_) {
        double sigma = building->value() * 0.1 / 3;
        double deltaValue = ValueGenerator::normalDistribution(0, sigma);
        double finalValue = deltaValue + building->value();
        building->setDeltaValue(deltaValue);
        building->setValue(finalValue);

		building->update();
    }
}

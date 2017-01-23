#include "BuildingManager.h"
#include "ValueGenerator.h"
#include "Residence.h"
#include "Commerce.h"
#include "Industry.h"
#include "Company.h"

BuildingManager::BuildingManager()
{
    buildingList_.push_back(new BuildingBase);
    for (int i = 0; i != 2; ++i)
        buildingList_.push_back(new Industry);
	for (int i = 0; i != 3; ++i)
		buildingList_.push_back(new Commerce);
    for (int i = 0; i != 5; ++i)
        buildingList_.push_back(new Residence);
}

BuildingBase *BuildingManager::getBuildingById(unsigned id) {
    return buildingList_[id];
}

const double BuildingManager::deltaValueOfCompanyProperties(Company *company) {
    double totalDeltaValue = 0;
    for (auto &building : buildingList_) {
		if (building->owner() == company)
			totalDeltaValue += building->deltaValue();
    }
    return totalDeltaValue;
}

BuildingBase *BuildingManager::setItemType(BuildingBase *building, const QString &type) {
    int id = buildingList_.indexOf(building);
    BuildingBase *newBuilding = nullptr;
    if (type == "Foundation")
        newBuilding = new BuildingBase(*building, type);
	else if (type.contains("Factory"))
		newBuilding = new Industry(*building, type);
	else if (type.contains("Commerce"))
		newBuilding = new Commerce(*building, type);
	else
        newBuilding = new Residence(*building, type);

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
    for (auto &building : buildingList_)
		building->update();
}

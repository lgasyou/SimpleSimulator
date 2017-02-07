#include "buildingmanager.h"
#include "buildingfactory.h"

#include "basebuilding.h"

#include "baseindustry.h"
#include "coalmine.h"
#include "ironmine.h"
#include "steelfactory.h"

#include "basecommerce.h"

#include "baseresidence.h"

#include "company.h"
#include "valuegenerator.h"

BuildingManager::BuildingManager() {
    buildingList_.push_back(new BaseBuilding);
	buildingList_.push_back(new CoalMine);
	buildingList_.push_back(new IronMine);
	buildingList_.push_back(new SteelFactory);
	for (int i = 0; i != 1; ++i)
		buildingList_.push_back(new BaseCommerce);
    for (int i = 0; i != 3; ++i)
        buildingList_.push_back(new BaseResidence);
}

BuildingManager::~BuildingManager() { }

BuildingManager &BuildingManager::instance() {
	static BuildingManager buildingManager;
	return buildingManager;
}

BaseBuilding *BuildingManager::getBuildingById(unsigned id) {
    return buildingList_[id];
}

const double BuildingManager::deltaValueOfCompanyProperties(Company *company) const {
    double totalDeltaValue = 0.0;
    for (auto &building : buildingList_) {
		if (building->owner() == company)
			totalDeltaValue += building->deltaValue();
    }
    return totalDeltaValue;
}

BaseBuilding *BuildingManager::resetItemType(BaseBuilding *building, const QString &type) {
	BuildingFactory buildingFactory;
    BaseBuilding *newBuilding = buildingFactory.create(type);
	newBuilding->copyInit(*building);

	auto &position = iteratorOf(building);
    delete *position;
	*position = newBuilding;
    return newBuilding;
}

void BuildingManager::addItem(BaseBuilding *building) {
    buildingList_.push_back(building);
}

void BuildingManager::removeItem(BaseBuilding *building) {
    buildingList_.removeOne(building);
}

void BuildingManager::update() {
    for (auto &building : buildingList_)
		building->update();
}

QList<BaseBuilding *>::iterator BuildingManager::iteratorOf(BaseBuilding *building) {
	auto &iterator = buildingList_.begin();
	while (iterator != buildingList_.end() && *iterator != building)
		++iterator;
	return iterator;
}

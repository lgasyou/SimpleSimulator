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
	BuildingFactory factory;
    buildingList_.push_back(factory.create("Foundation"));
	buildingList_.push_back(factory.create("Coal Mine"));
	buildingList_.push_back(factory.create("Iron Mine"));
	buildingList_.push_back(factory.create("Steel Factory"));
	for (int i = 0; i != 1; ++i)
		buildingList_.push_back(factory.create("Base Commerce"));
    for (int i = 0; i != 5; ++i)
        buildingList_.push_back(factory.create("Base Residence"));
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

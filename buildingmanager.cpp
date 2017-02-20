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

#include <algorithm>
#include <functional>
#include <QString>

BuildingManager::BuildingManager() {
	BuildingFactory factory;
    buildings_.push_back(factory.create("Foundation"));
	buildings_.push_back(factory.create("Coal Mine"));
	buildings_.push_back(factory.create("Iron Mine"));
	buildings_.push_back(factory.create("Steel Factory"));
	for (int i = 0; i != 1; ++i)
		buildings_.push_back(factory.create("Commerce"));
    for (int i = 0; i != 5; ++i)
        buildings_.push_back(factory.create("Residence"));
}

BuildingManager::~BuildingManager() { }

BuildingManager &BuildingManager::instance() {
	static BuildingManager buildingManager;
	return buildingManager;
}

double BuildingManager::deltaValueOfCompanyProperties(Company *company) const {
    double totalDeltaValue = 0.0;
    for (auto &building : buildings_) {
		if (building->owner() == company)
			totalDeltaValue += building->deltaValue();
    }
    return totalDeltaValue;
}

BaseBuilding *BuildingManager::resetItemType(BaseBuilding *building, const QString &type) {
	BuildingFactory buildingFactory;
    BaseBuilding *newBuilding = buildingFactory.create(type);
	newBuilding->copyFrom(*building);

	auto iterator = iteratorOf(building);
    delete *iterator;
	*iterator = newBuilding;
    return newBuilding;
}

void BuildingManager::addItem(BaseBuilding *building) {
    buildings_.push_back(building);
}

void BuildingManager::removeItem(BaseBuilding *building) {
	auto iter = iteratorOf(building);
	buildings_.erase(iter);
}

void BuildingManager::update() {
	std::for_each(buildings_.begin(), buildings_.end(), std::mem_fun(&BaseBuilding::update));
}

std::vector<BaseBuilding *>::iterator BuildingManager::iteratorOf(BaseBuilding *building) {
	auto &iterator = buildings_.begin();
	while (iterator != buildings_.end() && *iterator != building)
		++iterator;
	return iterator;
}

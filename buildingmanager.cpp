#include "buildingmanager.h"
#include "buildingfactory.h"

#include "basebuilding.h"

#include "company.h"
#include "valuegenerator.h"

#include <algorithm>
#include <functional>
#include <map>
#include <QString>

BuildingManager::BuildingManager() { }

BuildingManager::~BuildingManager() { }

BuildingManager &BuildingManager::instance() {
	static BuildingManager buildingManager;
	return buildingManager;
}

void BuildingManager::init() {
	BuildingFactory factory;
	addItem(factory.create("Unused Land"));
	addItem(factory.create("Mine"));
	addItem(factory.create("Mine"));
	addItem(factory.create("Factory"));
	addItem(factory.create("Bank"));
	addItem(factory.create("Supermarket"));
	addItem(factory.create("Garage"));
	for (int i = 0; i != 5; ++i)
		addItem(factory.create("Villa"));
}

BuildingManager::BuildingTypes BuildingManager::stringToEnum(const QString &type) {
	static std::map<QString, BuildingTypes> stringToEnumMap{
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

void BuildingManager::addItem(BaseBuilding *building) {
	buildings_.push_back(building);
}

double BuildingManager::deltaValueOfCompanyProperties(Company *company) const {
	double totalDeltaValue = 0.0;
	for (auto &building : buildings_) {
		if (building->owner() == company)
			totalDeltaValue += building->deltaValue();
	}
	return totalDeltaValue;
}

BaseBuilding *BuildingManager::getBuildingByPos(int x, int y) const {
	for (auto building : buildings_)
		if (building->position() == Vector2D(x, y))
			return building;
	return nullptr;
}


int BuildingManager::indexOf(BaseBuilding *building) const {
	for (int i = 0; i != buildings_.size(); ++i)
		if (buildings_[i] == building)
			return i;
	return -1;
}

void BuildingManager::removeItem(BaseBuilding *building) {
	auto iter = iteratorOf(building);
	buildings_.erase(iter);
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

void BuildingManager::update() {
	std::for_each(buildings_.begin(), buildings_.end(), std::mem_fun(&BaseBuilding::update));
}

std::vector<BaseBuilding *>::iterator BuildingManager::iteratorOf(BaseBuilding *building) {
	auto &iterator = buildings_.begin();
	while (iterator != buildings_.end() && *iterator != building)
		++iterator;
	return iterator;
}

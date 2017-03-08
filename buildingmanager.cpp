#include "buildingmanager.h"
#include "buildingfactory.h"

#include "basebuilding.h"

#include "company.h"
#include "valuegenerator.h"

#include "gameconstants.h"

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
	using namespace GameConstants;
	addItem(UnusedLand);
	addItem(Mine);
	addItem(Mine);
	addItem(Factory);
	addItem(Bank);
	addItem(Supermarket);
	addItem(Garage);
	for (int i = 0; i != 5; ++i)
		addItem(Villa);
}

GameConstants::BuildingTypes BuildingManager::stringToEnum(const QString &type) {
	using namespace GameConstants;
	static std::map<QString, GameConstants::BuildingTypes> stringToEnumMap{
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

void BuildingManager::addItem(GameConstants::BuildingTypes buildingType) {
	BuildingFactory factory;
	BaseBuilding *newBuilding = factory.create(buildingType);
	this->addItem(newBuilding);
}

double BuildingManager::deltaValueOfCompanyProperties(Company *company) const {
	double totalDeltaValue = 0.0;
	for (auto building : buildings_) {
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
	for (std::size_t i = 0; i != buildings_.size(); ++i)
		if (buildings_[i] == building)
			return static_cast<int>(i);
	return -1;
}

void BuildingManager::removeItem(BaseBuilding *building) {
	auto iter = iteratorOf(building);
	buildings_.erase(iter);
}

BaseBuilding *BuildingManager::resetItemType(BaseBuilding *building, GameConstants::BuildingTypes type) {
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
	auto iterator = buildings_.begin();
	while (iterator != buildings_.end() && *iterator != building)
		++iterator;
	return iterator;
}

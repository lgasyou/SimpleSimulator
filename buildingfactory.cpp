#include "buildingfactory.h"

#include "basebuilding.h"
#include "unusedland.h"

#include "baseindustry.h"
#include "factory.h"
#include "mine.h"

#include "basecommerce.h"
#include "supermarket.h"

#include "basefinance.h"
#include "bank.h"

#include "baseresidence.h"
#include "villa.h"

#include "baseagriculture.h"
#include "farm.h"

#include "basetransportation.h"
#include "garage.h"

#include "buildingmanager.h"
#include "mapmanager.h"
#include "government.h"

#include <QString>

BaseBuilding *BuildingFactory::create(const QString &type) {
	BaseBuilding *building = nullptr;

	auto buildingType = BuildingManager::stringToEnum(type);
	switch (buildingType) {
	case BuildingManager::Bank:
		building = new Bank;
		break;

	case BuildingManager::Factory:
		building = new Factory;
		break;

	case BuildingManager::Farm:
		building = new Farm;
		break;

	case BuildingManager::Garage:
		building = new Garage;
		break;

	case BuildingManager::Mine:
		building = new Mine;
		break;

	case BuildingManager::Supermarket:
		building = new Supermarket;
		break;

	case BuildingManager::UnusedLand:
		building = new UnusedLand;
		break;

	case BuildingManager::Villa:
		building = new Villa;
		break;

	default:
		break;
	}

	Government *gov = &Government::instance();
	building->setOwner(gov);

	Vector2D allocatedPos = MapManager::instance().allocate();
	building->setPosition(allocatedPos);

	// TODO
	// Generate true resource.
	building->setResource("Coal");

	return building;
}

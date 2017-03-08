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
#include "gameconstants.h"

#include <QString>

BaseBuilding *BuildingFactory::create(GameConstants::BuildingTypes buildingType) {
	BaseBuilding *building = nullptr;

	switch (buildingType) {
	case GameConstants::Bank:
		building = new Bank;
		break;

	case GameConstants::Factory:
		building = new Factory;
		break;

	case GameConstants::Farm:
		building = new Farm;
		break;

	case GameConstants::Garage:
		building = new Garage;
		break;

	case GameConstants::Mine:
		building = new Mine;
		break;

	case GameConstants::Supermarket:
		building = new Supermarket;
		break;

	case GameConstants::UnusedLand:
		building = new UnusedLand;
		break;

	case GameConstants::Villa:
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

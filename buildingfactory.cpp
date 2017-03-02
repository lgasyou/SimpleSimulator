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

#include "mapmanager.h"
#include "government.h"

#include <QString>

BaseBuilding *BuildingFactory::create(const QString &type) {
	BaseBuilding *building = nullptr;
	// Industrial buildings
	if (type == "Factory")
		building = new Factory;
	else if (type == "Mine")
		building = new Mine;

	// Commercial buildings
	else if (type == "Supermarket")
		building = new Supermarket;

	// Residential buildings
	else if (type == "Villa")
		building = new Villa;

	// Agricultural buildings
	else if (type == "Farm")
		building = new Farm;

	// Transporatation buildings
	else if (type == "Garage")
		building = new Garage;

	// Financial buildings
	else if (type == "Bank")
		building = new Bank;

	// Foundation
	else
		building = new UnusedLand;

	Vector2D allocatedPos = MapManager::instance().allocate();
	building->setPosition(allocatedPos);

	Government *gov = &Government::instance();
	building->setOwner(gov);

	return building;
}

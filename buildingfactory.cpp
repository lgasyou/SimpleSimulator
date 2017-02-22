#include "buildingfactory.h"

#include "basebuilding.h"
#include "unusedland.h"

#include "baseindustry.h"
#include "factory.h"
#include "mine.h"

#include "basecommerce.h"

#include "basefinance.h"

#include "baseresidence.h"

#include "baseagriculture.h"
#include "farm.h"

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
	else if (type == "Commerce")
		building = new BaseCommerce;

	// Residential buildings
	else if (type == "Residence")
		building = new BaseResidence;

	// Agricultural buildings
	else if (type == "Farm")
		building = new Farm;

	//else if (type == "Finance")
	//	building = new BaseFinance;

	// Foundation
	else
		building = new UnusedLand;

	Vector2D allocatedPos = MapManager::instance().allocate();
	building->setPosition(allocatedPos);

	Government *gov = &Government::instance();
	building->setOwner(gov);

	return building;
}

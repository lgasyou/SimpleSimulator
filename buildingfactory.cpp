#include "buildingfactory.h"

#include "basebuilding.h"

#include "baseindustry.h"
#include "factory.h"
#include "mine.h"

#include "basecommerce.h"

#include "baseresidence.h"

#include "baseagriculture.h"

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
	else if (type == "Agriculture")
		building = new BaseAgriculture;

	// Foundation
	else
		building = new BaseBuilding;

	Vector2D allocatedPos = MapManager::instance().allocate();
	building->setPosition(allocatedPos);

	Government *gov = &Government::instance();
	building->setOwner(gov);

	return building;
}

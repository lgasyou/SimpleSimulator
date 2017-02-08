#include "buildingfactory.h"

#include "basebuilding.h"

#include "baseindustry.h"
#include "coalmine.h"
#include "ironmine.h"
#include "steelfactory.h"

#include "basecommerce.h"

#include "baseresidence.h"

#include "baseagriculture.h"

#include "mapmanager.h"

#include <QString>

BaseBuilding *BuildingFactory::create(const QString &type) {
	BaseBuilding *building = nullptr;
	if (type == "Factory")
		building = new BaseIndustry;
	else if (type == "Coal Mine")
		building = new CoalMine;
	else if (type == "Iron Mine")
		building = new IronMine;
	else if (type == "Steel Factory")
		building = new SteelFactory;
	else if (type == "Base Commerce")
		building = new BaseCommerce;
	else if (type == "Base Residence")
		building = new BaseResidence;
	else if (type == "Base Agriculture")
		building = new BaseAgriculture;
	else
		building = new BaseBuilding;
	Vector2D allocatedPos = MapManager::instance().allocate();
	building->setPos(allocatedPos);
	return building;
}

#include "buildingfactory.h"

#include "basebuilding.h"

#include "baseindustry.h"
#include "coalmine.h"
#include "ironmine.h"
#include "steelfactory.h"

#include "basecommerce.h"

#include "baseresidence.h"

#include <QString>

BaseBuilding *BuildingFactory::create(const QString &type) {
	if (type == "Foundation")
		return new BaseBuilding;
	else if (type == "Factory")
		return new BaseIndustry;
	else if (type == "Coal Mine")
		return new CoalMine;
	else if (type == "Iron Mine")
		return new IronMine;
	else if (type == "Steel Factory")
		return new SteelFactory;
	else if (type == "BaseCommerce")
		return new BaseCommerce;
	else
		return new BaseResidence;
}

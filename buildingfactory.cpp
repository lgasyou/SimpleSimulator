#include "buildingfactory.h"

#include "basebuilding.h"

#include "industry.h"
#include "coalmine.h"
#include "ironmine.h"
#include "steelfactory.h"

#include "commerce.h"

#include "residence.h"

#include <QString>

BaseBuilding *BuildingFactory::create(const QString &type) {
	if (type == "Foundation")
		return new BaseBuilding;
	else if (type == "Factory")
		return new Industry;
	else if (type == "Coal Mine")
		return new CoalMine;
	else if (type == "Iron Mine")
		return new IronMine;
	else if (type == "Steel Factory")
		return new SteelFactory;
	else if (type == "Commerce")
		return new Commerce;
	else
		return new Residence;
}

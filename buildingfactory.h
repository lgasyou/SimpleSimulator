#ifndef BUILDINGFACTORY_H
#define BUILDINGFACTORY_H

#include "gameconstants.h"

class BaseBuilding;
class QString;

class BuildingFactory {
public:
	// Creates a new object and allocates a location to it.
	BaseBuilding *create(GameConstants::BuildingTypes);
};

#endif // !BUILDINGFACTORY_H
